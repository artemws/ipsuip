#include "functions.h"
#include "parallel_parsing.h"
#include "sync-ssl/http_client_sync_ssl.cpp"

std::map<std::string, std::string>
ipsuip::map_code(const std::vector<std::string> &_code) {
  std::map<std::string, std::string> _map;

  for (size_t value = 0, key = 1; key < _code.size(); value += 2, key += 2) {
    _map[_code[key]] = _code[value];
  }
  return _map;
}

void ipsuip::print_map(const std::map<std::string, std::string> &m) {
  for (const auto &[key, value] : m)
    std::cout << value << " --> " << key << "\n";
}

auto ipsuip::parsing_site(const std::string &code, const TYPEPARSING &TYPE) {
  std::string type;
  if (TYPE == TYPEPARSING::CONTINENT) {
    // https://suip.biz/?act=all-country-ip&continent=EU&all
    type = "/?act=all-country-ip&continent=" + code + "&all-download";
  }
  if (TYPE == TYPEPARSING::COUNTRY) {
    type = "/?act=all-country-ip&country=" + code + "&all-download";
  }

  std::vector<std::string> v{get("suip.biz", type)};
  std::vector<std::string> v2;

  parallel_work(v.begin(), v.end(), v2, VAR::PARSING_DATA_S);

  if (v2.empty())
    throw std::runtime_error("Buffer empty");
  return v;
}

void ipsuip::run_init(const std::string &code, const std::string &path,
                      std::map<std::string, std::string> _map,
                      const TYPEPARSING &TYPE) {
  std::string spath{path};

  if (spath.back() != '/')
    spath.push_back('/');

  if (size_t pos{spath.find_first_of(".", 1)}; pos != std::string::npos) {
    spath.erase(pos);
  }

  std::filesystem::path path_{spath};

  if (!std::filesystem::exists(path_))
    std::filesystem::create_directories(path_);

  std::vector<std::string> data{parsing_site(code, TYPE)};

  std::cout << "Start for    --> " << _map[code] << "\n";
  std::cout << "Path to save --> " + std::string(path_) + _map[code] << "\n";

  std::vector<std::string> v;

  parallel_work(data.begin(), data.end(), v, VAR::TO_RANGE_S);
  save_to_file(v, path_.string() + _map[code] + "_RANGE.txt");

  parallel_work(data.begin(), data.end(), v, VAR::TO_CIDR_S);
  save_to_file(v, path_.string() + _map[code] + "_CIDR.txt");

  std::cout << "Saved two files --> " + path_.string() + _map[code] +
                   "_RANGE.txt and "
            << path_.string() + _map[code] + "_CIDR.txt\n";
}

bool ipsuip::validateIP(const std::string &ip) {
  boost::system::error_code ec;
  boost::asio::ip::make_address_v4(ip, ec);

  if (ec)
    return false;
  return true;
}

void ipsuip::get_parsing_data(const std::vector<std::string>::iterator &first,
                              const std::vector<std::string>::iterator &second,
                              std::vector<std::string> &result)
{
  std::vector<std::string> v;

  for (auto it{first}; it != second; ++it) {
    for (size_t i{it->find_first_not_of("0123456789.-")};
         it->size() >= 15 && i != std::string::npos;) {
        it->erase(i, 1);
        i = it->find_first_not_of("0123456789.-");
    }

    if (std::isdigit(it->back()) && std::isdigit(it->front()))
        v.emplace_back(*it);
  }

  result = v;
}

void ipsuip::to_cidr(const std::vector<std::string>::iterator &first,
                     const std::vector<std::string>::iterator &second,
                     std::vector<std::string> &result)
{
  std::vector<std::string> v_cidr;

  for (auto it{first}; it != second; ++it) {
    std::stringstream s(*it);

    std::string first_ip;
    std::string second_ip;

    std::getline(s, first_ip, '-');
    std::getline(s, second_ip);

    if (validateIP(first_ip) && validateIP(second_ip)) {
        std::vector<std::string> v_temp = range_boundaries_to_cidr(

            boost::asio::ip::make_address_v4(first_ip).to_uint(),
            boost::asio::ip::make_address_v4(second_ip).to_uint());

        v_cidr.insert(v_cidr.end(), v_temp.cbegin(), v_temp.cend());

    } else
        continue;
  }

  result = v_cidr;
}

void ipsuip::to_range(const std::vector<std::string>::iterator &first,
                      const std::vector<std::string>::iterator &second,
                      std::vector<std::string> &result)
{
  std::vector<std::string> v_range;

  for (auto it{first}; it != second; ++it) {
    std::stringstream s(*it);

    std::string first_ip;
    std::string second_ip;

    std::getline(s, first_ip, '-');
    std::getline(s, second_ip);

    if (validateIP(first_ip) && validateIP(second_ip)) {
        v_range.emplace_back(first_ip + "-" + second_ip);

    } else
        continue;
  }

  result = v_range;
}

const std::vector<std::string> ipsuip::range_boundaries_to_cidr(const long int &ip_start,
                                                                const long int &ip_end)
{
  uint8_t bits = 1;
  long int mask = 1;
  long int new_ip;
  std::stringstream ss;
  std::vector<std::string> cidrs;

  while (bits < 32) {
    new_ip = ip_start | mask;
    if ((new_ip > ip_end) || (((ip_start >> bits) << bits) != ip_start)) {
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

  if (new_ip <
      ip_end) { // if we're not done, compute more and join everything together
    std::vector<std::string> tmp_cidrs =
        range_boundaries_to_cidr(new_ip + 1, ip_end);
    cidrs.insert(cidrs.end(), tmp_cidrs.begin(), tmp_cidrs.end());
  }

  return cidrs;
}

void ipsuip::save_to_file(const std::vector<std::string> &v_ip, const std::string &file_name)
{
  if (v_ip.empty())
    throw std::runtime_error("vector empty");

  std::ofstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    file.open(file_name);
    if (!file)
      throw std::runtime_error("File creation error: " + file_name);

    for (const auto &i : v_ip)
      file << i << "\n";
    file.close();

    std::filesystem::path path{file_name};
    if (std::filesystem::exists(path))
      std::cout << "Size of " + file_name + " "
                << HumanReadable{std::filesystem::file_size(path)} << "\n";
  } catch (std::ofstream::failure &e) {
    std::cerr << e.what() << " code: " << e.code() << std::endl;
  }
}

const std::string ipsuip::get_path(std::string path, const std::string &code,
                                   std::map<std::string, std::string> m) {
  if (path.back() != '/')
    path.push_back('/');

  path.append(m[code] + "/");
  return path;
}
