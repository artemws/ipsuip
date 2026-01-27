#pragma once
#include "functions.h"
#include "timer.h"
#include <iostream>
#include <string>
#include <vector>

void choose_your_fate(int argc, char **argv)
{
    std::vector<std::string> cmd(argv, argv + argc);

    const std::string help{"--help"}, output{"--output"}, output_sh{"-o"}, help_sh{"-h"},
        mainland{"--mainland"}, mainland_sh{"-m"}, country{"--country"}, country_sh{"-c"},
        all{"--all"};

    /////////////////////////////////////////////////////////
    /// USAGE
    /// /////////////////////////////////////////////////////
    if (cmd.size() == 1 || cmd.size() > 5 || cmd.size() == 3) {
        std::cerr << "Usage: ipcountriesdownloader [OPTION]\n"
                  << "Try 'ipcountriesdownloader --help' for more information.\n";
        return;
    }

    if (cmd.size() == 2) {
        ///////////////////////////////////////////////////
        /// HELP
        /// ///////////////////////////////////////////////
        if (cmd[1] == help || cmd[1] == help_sh) {
            std::cout << ipsuip::help_out << std::endl;
            return;
        }

        ////////////////////////////////////////////////////
        /// MAINLAND COUNTRY
        /// ////////////////////////////////////////////////
        else if (cmd[1] == mainland || cmd[1] == mainland_sh || cmd[1] == country
                 || cmd[1] == country_sh) {
            if (cmd[1] == mainland || cmd[1] == mainland_sh) {
                ipsuip::print_map(ipsuip::map_code(ipsuip::mainland_code_data));
            } else if (cmd[1] == country || cmd[1] == country_sh) {
                ipsuip::print_map(ipsuip::map_code(ipsuip::country_code_data));
            }

            return;
        }

        ////////////////////////////////////////////////////
        ///
        /// ////////////////////////////////////////////////
        else if (cmd[1] == all) {
            throw std::runtime_error("Directory not specified! Use -o OR --output");
        } else {
            throw std::runtime_error("Argument not correct: " + cmd[1]);
        }
    }

    //////////////////////////////////////////////////////////
    /// DOWNLOAD ALL MAINLANDS COUNTRIES
    /// //////////////////////////////////////////////////////
    else if ((cmd.size() == 5 && cmd[1] == all && (cmd[2] == country_sh || cmd[2] == mainland_sh)
              && (cmd[3] == output_sh || cmd[3] == output))
             || (cmd.size() == 5 && cmd[1] == all && (cmd[2] == country || cmd[2] == mainland)
                 && (cmd[3] == output_sh || cmd[3] == output))) {
        Timer timer;

        if (cmd[2] == mainland_sh || cmd[2] == mainland) {
            for (const auto &code : ipsuip::codes_mainlands) {
                ipsuip::run_init(code,
                                 ipsuip::get_path(cmd[4],
                                                  code,
                                                  ipsuip::map_code(ipsuip::mainland_code_data)),
                                 ipsuip::map_code(ipsuip::mainland_code_data),
                                 ipsuip::TYPEPARSING::CONTINENT);
            }
        } else

            if (cmd[2] == country_sh || cmd[2] == country) {
            for (const auto &code : ipsuip::codes_countries) {
                ipsuip::run_init(code,
                                 ipsuip::get_path(cmd[4],
                                                  code,
                                                  ipsuip::map_code(ipsuip::country_code_data)),
                                 ipsuip::map_code(ipsuip::country_code_data),
                                 ipsuip::TYPEPARSING::COUNTRY);
            }
        }

        return;
    }

    //////////////////////////////////////////////////////////////
    ///   MAINLAND COUNTRY
    /// //////////////////////////////////////////////////////////
    else if ((cmd.size() == 5 && cmd[3] == output_sh) || (cmd.size() == 5 && cmd[3] == output)) {
        Timer timer;

        if ((cmd[1] == mainland && ipsuip::codes_mainlands.contains(cmd[2]))
            || (cmd[1] == mainland_sh && ipsuip::codes_mainlands.contains(cmd[2]))) {
            ipsuip::run_init(cmd[2],
                             cmd[4],
                             ipsuip::map_code(ipsuip::mainland_code_data),
                             ipsuip::TYPEPARSING::CONTINENT);
        } else if ((cmd[1] == country && ipsuip::codes_countries.contains(cmd[2]))
                   || (cmd[1] == country_sh && ipsuip::codes_countries.contains(cmd[2]))) {
            ipsuip::run_init(cmd[2],
                             cmd[4],
                             ipsuip::map_code(ipsuip::country_code_data),
                             ipsuip::TYPEPARSING::COUNTRY);
        } else {
            throw std::runtime_error(cmd[2] + " this is the wrong argument!");
        }

        return;
    }

    ////////////////////////////////////////////////////////////////////
    ///
    /// ////////////////////////////////////////////////////////////////
    else {
        throw std::runtime_error("Argument not valid!");
    }

    return;
}
