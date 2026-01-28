#pragma once

// #include "http_client_sync_ssl.h"
// #include "parallel_parsing.h"
#include "root_certificates.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl/ssl_stream.hpp>
#include <boost/regex.hpp>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace ipsuip {

extern const std::string help_out;

extern const std::set<std::string> codes_mainlands;

extern const std::set<std::string> codes_countries;

extern const std::vector<std::string> mainland_code_data;

extern const std::vector<std::string> country_code_data;

enum class TYPEPARSING { CONTINENT, COUNTRY };

const std::string get_path(std::string path, const std::string &code,
                           std::map<std::string, std::string> m);

struct HumanReadable {
  std::uintmax_t size{};

  HumanReadable(std::uintmax_t size) : size{size} {}

private:
  friend std::ostream &operator<<(std::ostream &os, ipsuip::HumanReadable hr) {
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

std::map<std::string, std::string>
map_code_revers(const std::vector<std::string> &_code);

void print_map(const std::map<std::string, std::string> &m);

enum class VAR { PARSING_DATA_S, TO_CIDR_S, TO_RANGE_S };

void get_parsing_data(const std::vector<std::string>::iterator &first,
                      const std::vector<std::string>::iterator &second,
                      std::vector<std::string> &result);

template <typename Iterator> struct parsing_data_s {
  void operator()(Iterator first, Iterator last,
                  std::vector<std::string> &result) {
    get_parsing_data(first, last, result);
  }
};

void to_cidr(const std::vector<std::string>::iterator &first,
             const std::vector<std::string>::iterator &second,
             std::vector<std::string> &result);

template <typename Iterator> struct to_cidr_s {
  void operator()(Iterator first, Iterator last,
                  std::vector<std::string> &result) {
    to_cidr(first, last, result);
  }
};

void to_range(const std::vector<std::string>::iterator &first,
              const std::vector<std::string>::iterator &second,
              std::vector<std::string> &result);

template <typename Iterator> struct to_range_s {
  void operator()(Iterator first, Iterator last,
                  std::vector<std::string> &result) {
    to_range(first, last, result);
  }
};

template <typename Iterator>
void parallel_work(Iterator first, Iterator last,
                   std::vector<std::string> &init, const VAR &var) {
  unsigned long const length = std::distance(first, last);

  if (!length)
    return;

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads =
      (length + min_per_thread - 1) / min_per_thread;

  unsigned long const hardware_threads = std::thread::hardware_concurrency();

  unsigned long const num_threads =
      std::min(hardware_threads != 0 ? hardware_threads : 4, max_threads);

  unsigned long const block_size = length / num_threads;

  std::vector<std::vector<std::string>> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);

  Iterator block_start = first;

  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_end = block_start;

    std::advance(block_end, block_size);
    if (var == VAR::PARSING_DATA_S) {
      threads[i] = std::thread(parsing_data_s<Iterator>(), block_start,
                               block_end, std::ref(results[i]));
    } else if (var == VAR::TO_RANGE_S) {
      threads[i] = std::thread(to_range_s<Iterator>(), block_start, block_end,
                               std::ref(results[i]));
    } else if (var == VAR::TO_CIDR_S) {
      threads[i] = std::thread(to_cidr_s<Iterator>(), block_start, block_end,
                               std::ref(results[i]));
    }

    block_start = block_end;
  }

  if (var == VAR::PARSING_DATA_S)
    parsing_data_s<Iterator>()(block_start, last, results[num_threads - 1]);
  else if (var == VAR::TO_RANGE_S)
    to_range_s<Iterator>()(block_start, last, results[num_threads - 1]);
  else if (var == VAR::TO_CIDR_S)
    to_cidr_s<Iterator>()(block_start, last, results[num_threads - 1]);

  std::for_each(threads.begin(), threads.end(),
                std::mem_fn(&std::thread::join));

  std::vector<std::string> v;
  for (const auto &i : results)
    v.insert(v.end(), i.begin(), i.end());

  init = v;
}

auto parsing_site(const std::string &code, const TYPEPARSING &TYPE);

bool validateIP(const std::string &ip);

void save_to_file(const std::vector<std::string> &v_ip,
                  const std::string &file_name);

void run_init(const std::string &code, const std::string &path,
              std::map<std::string, std::string> _map, const TYPEPARSING &TYPE);

const std::vector<std::string>
range_boundaries_to_cidr(const long int &ip_start, const long int &ip_end);
struct IP_a {
  std::vector<std::string> RANGE;
  std::vector<std::string> CIDR;
};

} // namespace ipsuip
