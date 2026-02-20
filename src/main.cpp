#include "functions.h"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << ipsuip::help_out;
        return 0;
    }

    std::string output_path = "./";
    std::string code;
    ipsuip::TYPEPARSING type = ipsuip::TYPEPARSING::COUNTRY;
    bool all = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h") {
            std::cout << ipsuip::help_out;
            return 0;
        }
        else if (arg == "-c" || arg == "--country") {
            type = ipsuip::TYPEPARSING::COUNTRY;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                code = argv[++i];
            } else {
                // без аргумента — напечатать список кодов стран
                ipsuip::print_map(ipsuip::map_code(ipsuip::country_code_data));
                return 0;
            }
        }
        else if (arg == "-m" || arg == "--mainland") {
            type = ipsuip::TYPEPARSING::CONTINENT;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                code = argv[++i];
            } else {
                // без аргумента — напечатать список кодов материков
                ipsuip::print_map(ipsuip::map_code(ipsuip::mainland_code_data));
                return 0;
            }
        }
        else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                output_path = argv[++i];
            } else {
                std::cerr << "Error: -o requires a path argument\n";
                return 1;
            }
        }
        else if (arg == "--all") {
            all = true;
        }
        else {
            std::cerr << "Unknown argument: " << arg << "\n";
            std::cout << ipsuip::help_out;
            return 1;
        }
    }

    try {
        if (all) {
            if (type == ipsuip::TYPEPARSING::COUNTRY) {
                auto m = ipsuip::map_code(ipsuip::country_code_data);
                for (const auto &[name, c] : m)
                    ipsuip::run_init(c, output_path, m, ipsuip::TYPEPARSING::COUNTRY);
            } else {
                auto m = ipsuip::map_code(ipsuip::mainland_code_data);
                for (const auto &[name, c] : m)
                    ipsuip::run_init(c, output_path, m, ipsuip::TYPEPARSING::CONTINENT);
            }
        } else {
            if (code.empty()) {
                std::cerr << "Error: no country/mainland code specified\n";
                std::cout << ipsuip::help_out;
                return 1;
            }
            if (type == ipsuip::TYPEPARSING::COUNTRY) {
                if (ipsuip::codes_countries.find(code) == ipsuip::codes_countries.end()) {
                    std::cerr << "Error: unknown country code '" << code << "'\n";
                    return 1;
                }
                ipsuip::run_init(code, output_path,
                                 ipsuip::map_code(ipsuip::country_code_data),
                                 ipsuip::TYPEPARSING::COUNTRY);
            } else {
                if (ipsuip::codes_mainlands.find(code) == ipsuip::codes_mainlands.end()) {
                    std::cerr << "Error: unknown mainland code '" << code << "'\n";
                    return 1;
                }
                ipsuip::run_init(code, output_path,
                                 ipsuip::map_code(ipsuip::mainland_code_data),
                                 ipsuip::TYPEPARSING::CONTINENT);
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
