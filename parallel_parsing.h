#pragma once

#include "functions.h"
#include <functional>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>

enum class VAR { PARSING_DATA_S, TO_CIDR_S, TO_RANGE_S };

template<typename Iterator>
struct parsing_data_s
{
    void operator()(Iterator first, Iterator last, std::vector<std::string> &result)
    {
        ipsuip::get_parsing_data(first, last, result);
    }
};

template<typename Iterator>
struct to_cidr_s
{
    void operator()(Iterator first, Iterator last, std::vector<std::string> &result)
    {
        ipsuip::to_cidr(first, last, result);
    }
};
template<typename Iterator>
struct to_range_s
{
    void operator()(Iterator first, Iterator last, std::vector<std::string> &result)
    {
        ipsuip::to_range(first, last, result);
    }
};

template<typename Iterator>
void parallel_work(Iterator first, Iterator last, std::vector<std::string> &init, const VAR &var)
{
    unsigned long const length = std::distance(first, last);

    if (!length)
        return;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;

    unsigned long const hardware_threads = std::thread::hardware_concurrency();

    unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2,
                                               max_threads);

    unsigned long const block_size = length / num_threads;

    std::vector<std::vector<std::string>> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator block_start = first;

    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;

        std::advance(block_end, block_size);
        if (var == VAR::PARSING_DATA_S) {
            threads[i] = std::thread(parsing_data_s<Iterator>(),
                                     block_start,
                                     block_end,
                                     std::ref(results[i]));
        } else if (var == VAR::TO_RANGE_S) {
            threads[i] = std::thread(to_range_s<Iterator>(),
                                     block_start,
                                     block_end,
                                     std::ref(results[i]));
        } else if (var == VAR::TO_CIDR_S) {
            threads[i] = std::thread(to_cidr_s<Iterator>(),
                                     block_start,
                                     block_end,
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

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    std::vector<std::string> v;
    for (const auto &i : results)
        v.insert(v.end(), i.begin(), i.end());

    init = v;
}
