#pragma once
#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace ipsuip
{
const std::map<std::string, std::string>
map_code(const std::vector<std::string> &_code)
{
    std::map<std::string, std::string> _map;

    for (size_t value = 0, key = 1; key < _code.size(); value += 2, key += 2)
    {
        _map[_code[key]] = _code[value];
    }
    return _map;
}

void print_map(const std::map<std::string, std::string> &m)
{
    for (const auto &[key, value] : m)
        std::cout << value << " --> " << key << "\n";
}

enum class TYPEPARSING
{
    CONTINENT,
    COUNTRY
};

const std::string parsing_site(const std::string &code, const std::string &path,
                               TYPEPARSING TYPE)
{
    std::string type;
    if (TYPE == TYPEPARSING::CONTINENT)
    {
        type = "continent";
    }
    if (TYPE == TYPEPARSING::COUNTRY)
    {
        type = "country";
    }

    return std::string(
        "echo '# Start download #' && wget -q -E "
        "\"https://suip.biz/?act=all-country-ip&" +
        type + "=" + code +
        "&all\" "
        "&& echo '# End download #' && echo '# Start parsing ip "
        "addreses #' && cat index.* "
        "| "
        "grep -Eo "
        "'(((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|"
        "2[0-"
        "4]"
        "[0-9]|[01]?[0-9][0-9]?)\\-((25[0-5]|2[0-4][0-9]|[01]?[0-9]"
        "[0-"
        "9]"
        "?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))' > " +
        path.c_str() + "ip" + code +
        "_RANGES.txt && echo '# Create ipranges file #' && gawk -E "
        "./ip2cidr.awk " +
        path.c_str() + "ip" + code + "_RANGES.txt > " + path.c_str() + "ip" +
        code +
        "_CIDR.txt && echo '# Create ipcidr file #' && echo '# "
        "Clean temp files #' && rm index.html* && echo '# All "
        "done! #'");
}

void run_init(const std::string code, std::string spath,
              std::map<std::string, std::string> &_map, TYPEPARSING TYPE)
{

    if (spath.back() != '/')
        spath.push_back('/');

    std::filesystem::path path{spath};

    if (!std::filesystem::exists(path))
        std::filesystem::create_directories(path);

    const std::string SITE{parsing_site(code, path, TYPE)};
    std::cout << "### Start for " << _map[code] << "\n";
    system(SITE.c_str());
}
} // namespace ipsuip
