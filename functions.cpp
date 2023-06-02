#include "functions.h"
#include "sync-ssl/http_client_sync_ssl.cpp"

//namespace ipsuip
//{

const std::map<std::string, std::string> ipsuip::map_code(const std::vector<std::string> &_code)
{
    std::map<std::string, std::string> _map;

    for (size_t value = 0, key = 1; key < _code.size(); value += 2, key += 2)
    {
        _map[_code[key]] = _code[value];
    }
    return _map;
}

void ipsuip::print_map(const std::map<std::string, std::string> &m)
{
    for (const auto &[key, value] : m)
        std::cout << value << " --> " << key << "\n";
}

auto ipsuip::parsing_site(const std::string &code, const TYPEPARSING &TYPE)
{
    std::string type;
    if (TYPE == TYPEPARSING::CONTINENT)
    {
        // https://suip.biz/?act=all-country-ip&continent=EU&all
        type = "/?act=all-country-ip&continent=" + code + "&all-download";
    }
    if (TYPE == TYPEPARSING::COUNTRY)
    {
        type = "/?act=all-country-ip&country=" + code + "&all-download";
    }

    return std::stringstream(get("suip.biz", type));
}

void ipsuip::write(std::filesystem::path &path, const std::string &code, const std::string &data)
{
    std::ofstream ofs;
    ofs.open(path.c_str() + code + ".txt");
    if (!ofs)
        throw std::runtime_error("Error create file " +
                                 std::string(path.c_str()));

    ofs << data;
}

void ipsuip::run_init(const std::string &code,
                      std::string &spath,
                      std::map<std::string, std::string> &_map,
                      const TYPEPARSING &TYPE)
{

    if (spath.back() != '/')
        spath.push_back('/');

    std::filesystem::path path{spath};

    if (!std::filesystem::exists(path))
        std::filesystem::create_directories(path);

    std::stringstream SITE = parsing_site(code, TYPE);
    std::cout << "### Start for " << _map[code] << "\n";
    std::cout << "Full path: " + std::string(path.c_str()) + _map[code] << "\n";
    // std::cout << SITE.str() << std::endl;
    clean_page_to_ip4_range(SITE, path.c_str() + _map[code],
                            VARIANT_VECTOR::ALL);
}

// IP address lists of Armenia страна скачивание сразу

// All IP ranges of Oceania континент страничка html
// std::stringstream ss2(get("suip.biz",
// "/?act=all-country-ip&continent=OC&all"));

// IP addresses lists. All Cities of Lovech провинции скачивание сразу
// std::stringstream ss3(get("suip.biz",
// "/?act=all-country-ip&province=Lovech&all-download"));

bool ipsuip::isNumber(const std::string &str)
{
    return !str.empty() &&
           (str.find_first_not_of("0123456789") == std::string::npos);
}

std::vector<std::string> ipsuip::split(const std::string &str, char delim)
{
    auto i = 0;
    std::vector<std::string> list;

    auto pos = str.find(delim);

    while (pos != std::string::npos)
    {
        list.push_back(str.substr(i, pos - i));
        i = ++pos;
        pos = str.find(delim, pos);
    }

    list.push_back(str.substr(i, str.length()));

    return list;
}

bool ipsuip::validateIP(const std::string &ip)
{
    // split the string into tokens
    std::vector<std::string> list = split(ip, '.');

    // if the token size is not equal to four
    if (list.size() != 4)
    {
        return false;
    }

    // validate each token
    for (const std::string &str : list)
    {
        // verify that the string is a number or not, and the numbers
        // are in the valid range
        if (!isNumber(str) || stoi(str) > 255 || stoi(str) < 0)
        {
            return false;
        }
    }

    return true;
}

// 1.1.1.1-1.1.1.2
bool ipsuip::clear_string(std::string &str)
{

    for (size_t i{str.find_first_not_of("0123456789.-")};
         str.size() >= 15 && i != std::string::npos;)
    {
        str.erase(i, 1);
        i = str.find_first_not_of("0123456789.-");
    }

    if (std::isdigit(str.back()) && std::isdigit(str.front()))
        return true;

    return false;
}

const std::pair<std::vector<std::string>, std::vector<std::string>> ipsuip::clean_page_to_ip4_range(
    std::stringstream &html_page,
    const std::string &file_to_save,
    const VARIANT_VECTOR &variant_vector)
{

    std::vector<std::string> v;
    std::vector<std::string> v_cidr;
    std::vector<std::string> v_range;

    std::string file_to_save_cp{file_to_save};

    if (size_t pos{file_to_save.find_first_of(".", 1)};
        pos != std::string::npos)
    {
        file_to_save_cp.erase(pos);
    }

    for (std::string iprange; getline(html_page, iprange);)

    {
        if (!clear_string(iprange))
        {
            continue;
        }

        std::stringstream s;
        std::string first_ip;
        std::string second_ip;

        int octet1[4] = {};
        int octet2[4] = {};
        char c;

        s << iprange;

        for (int n = 0; n < 4; ++n)
            s >> octet1[n] >> c;

        for (int n = 0; n < 4; ++n)
            s >> octet2[n] >> c;

        first_ip.append(std::to_string(octet1[0]))
            .append(".")
            .append(std::to_string(octet1[1]))
            .append(".")
            .append(std::to_string(octet1[2]))
            .append(".")
            .append(std::to_string(octet1[3]));

        second_ip.append(std::to_string(octet2[0]))
            .append(".")
            .append(std::to_string(octet2[1]))
            .append(".")
            .append(std::to_string(octet2[2]))
            .append(".")
            .append(std::to_string(octet2[3]));

        if (validateIP(first_ip) && validateIP(second_ip))
        {
            if (VARIANT_VECTOR::CIDR == variant_vector ||
                VARIANT_VECTOR::ALL == variant_vector)
            {
                std::vector<std::string> v_temp = range_boundaries_to_cidr(
                    boost::asio::ip::make_address_v4(first_ip).to_uint(),
                    boost::asio::ip::make_address_v4(second_ip).to_uint());

                v_cidr.insert(v_cidr.end(), v_temp.begin(), v_temp.end());
            }

            if (VARIANT_VECTOR::RANGE == variant_vector ||
                VARIANT_VECTOR::ALL == variant_vector)
            {
                v_range.emplace_back(first_ip + "-" + second_ip);
            }
        }
        else
            continue;
    }

    try
    {
        if (VARIANT_VECTOR::ALL == variant_vector)
        {
            save_to_file(v_range, file_to_save_cp + "_RANGE.txt");
            save_to_file(v_cidr, file_to_save_cp + "_CIDR.txt");
        }
        else if (VARIANT_VECTOR::RANGE == variant_vector)
        {

            save_to_file(v_range, file_to_save_cp + "_RANGE.txt");
        }
        else if (VARIANT_VECTOR::CIDR == variant_vector)
        {

            save_to_file(v_cidr, file_to_save_cp + "_CIDR.txt");
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return std::pair<std::vector<std::string>, std::vector<std::string>>(
        std::make_pair(v_range, v_cidr));
}

const std::vector<std::string> ipsuip::range_boundaries_to_cidr(long int ip_start, long int ip_end)
{
    uint8_t bits = 1;
    long int mask = 1;
    long int new_ip;
    std::stringstream ss;
    std::vector<std::string> cidrs;

    while (bits < 32)
    {
        new_ip = ip_start | mask;
        if ((new_ip > ip_end) || (((ip_start >> bits) << bits) != ip_start))
        {
            bits--;
            mask = mask >> 1;
            break;
        }
        bits++;
        mask = (mask << 1) + 1;
    }

    new_ip = ip_start | mask;
    bits = 32 - bits;

    // get the first (possibly only) CIDR block
    ss << static_cast<long int>(bits);
    cidrs.emplace_back(boost::asio::ip::address_v4(ip_start).to_string() + "/" +
                       ss.str());

    if (new_ip < ip_end)
    { // if we're not done, compute more and join everything together
        std::vector<std::string> tmp_cidrs =
            range_boundaries_to_cidr(new_ip + 1, ip_end);
        cidrs.insert(cidrs.end(), tmp_cidrs.begin(), tmp_cidrs.end());
    }

    return cidrs;
}

bool ipsuip::read_from_file(std::ifstream &file, const std::string &str)
{
    try
    {
        file.open(str);
        if (!file)
            throw std::runtime_error("File open error!");
    }
    catch (std::ifstream::failure &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return true;
}

bool ipsuip::save_to_file(const std::vector<std::string> &v_ip, const std::string &file_name)
{
    std::ofstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(file_name);
        if (!file)
            throw std::runtime_error("File creation error!");

        if (v_ip.empty())
            throw std::runtime_error("vector empty");

        for (const auto &i : v_ip)
            file << i << "\n";
        file.close();

        std::filesystem::path path{file_name};
        if (std::filesystem::exists(path))
            std::cout << "Size of " + file_name + " "
                      << HumanReadable{std::filesystem::file_size(path)}
                      << "\n";
    }
    catch (std::ofstream::failure &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

//} // namespace ipsuip
