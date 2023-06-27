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

const std::string get_path(std::string path, const std::string &code,
                           std::map<std::string, std::string> m);

struct HumanReadable {
  std::uintmax_t size{};

  HumanReadable(std::uintmax_t size) : size{size} {}

private:
  friend std::ostream &operator<<(std::ostream &os, HumanReadable hr) {
    int i{};
    double mantissa = hr.size;
    for (; mantissa >= 1024.; mantissa /= 1024., ++i) {
    }
    mantissa = std::ceil(mantissa * 10.) / 10.;
    os << mantissa << "BKMGTPE"[i];
    return i == 0 ? os : os << "B (" << hr.size << ')';
  }
};

std::map<std::string, std::string>
map_code(const std::vector<std::string> &_code);

void print_map(const std::map<std::string, std::string> &m);

auto parsing_site(const std::string &code, const TYPEPARSING &TYPE);

void run_init(const std::string &code, const std::string &path,
              std::map<std::string, std::string> _map, const TYPEPARSING &TYPE);

void to_range(const std::vector<std::string>::iterator &first,
              const std::vector<std::string>::iterator &second,
              std::vector<std::string> &result);

void to_cidr(const std::vector<std::string>::iterator &first,
             const std::vector<std::string>::iterator &second,
             std::vector<std::string> &result);

const std::vector<std::string> range_boundaries_to_cidr(const long int &ip_start,
                                                        const long int &ip_end);

// bool read_from_file(std::ifstream &file, const std::string &str);

void save_to_file(const std::vector<std::string> &v_ip,
                  const std::string &file_name);

void get_parsing_data(const std::vector<std::string>::iterator &first,
                      const std::vector<std::string>::iterator &second,
                      std::vector<std::string> &result);

bool validateIP(const std::string &ip);

struct IP_a {
  std::vector<std::string> RANGE;
  std::vector<std::string> CIDR;
};

} // namespace ipsuip
