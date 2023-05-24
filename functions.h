#pragma once
#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace ipsuip
{

const std::map<std::string, std::string>
map_code(const std::vector<std::string> &_code);

void print_map(const std::map<std::string, std::string> &m);

enum class TYPEPARSING
{
    CONTINENT,
    COUNTRY
};

const std::string parsing_site(const std::string &code, const std::string &path,
                               TYPEPARSING TYPE);

void run_init(const std::string& code, std::string& spath,
              std::map<std::string, std::string> &_map, const TYPEPARSING& TYPE);

} // namespace ipsuip
