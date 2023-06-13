#pragma once

#include "enum_variants.h"
#include <boost/asio.hpp>
#include <boost/regex.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace ipsuip {

const std::string get_path(std::string path,
                           const std::string &code,
                           std::map<std::string, std::string> m);

struct HumanReadable
{
    std::uintmax_t size{};

private:
    friend std::ostream &operator<<(std::ostream &os, HumanReadable hr)
    {
        int i{};
        double mantissa = hr.size;
        for (; mantissa >= 1024.; mantissa /= 1024., ++i) {
        }
        mantissa = std::ceil(mantissa * 10.) / 10.;
        os << mantissa << "BKMGTPE"[i];
        return i == 0 ? os : os << "B (" << hr.size << ')';
    }
};

std::map<std::string, std::string> map_code(const std::vector<std::string> &_code);

void print_map(const std::map<std::string, std::string> &m);

auto parsing_site(const std::string &code, const TYPEPARSING &TYPE);

void run_init(const std::string &code,
              const std::string &path,
              std::map<std::string, std::string> _map,
              const TYPEPARSING &TYPE);

//@@ clean site page and return pair vector CIDR and RANGE ip addreses
const std::pair<std::vector<std::string>, std::vector<std::string>>
clean_page_to_ip4_list(std::stringstream &html_page,
                        const std::string &file_to_save,
                        const VARIANT_VECTOR &variant_vector);

const std::vector<std::string> range_boundaries_to_cidr(long ip_start,
                                                        long ip_end);

bool read_from_file(std::ifstream &file, const std::string &str);

bool save_to_file(const std::vector<std::string> &v_ip, const std::string &file_name);

bool get_parsing_string(std::string &str);

bool validateIP(const std::string &ip);

struct IP_a
{
    std::vector<std::string> RANGE;
    std::vector<std::string> CIDR;
};

} // namespace ipsuip
