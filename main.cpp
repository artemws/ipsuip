/** Made by I'Pancake **/

#include "countries.h"
#include "functions.h"
#include "timer.h"
// #include <filesystem>
#include <fstream>
// #include <iostream>
// #include <map>
// #include <set>
// #include <string>
// #include <vector>

int main(int argc, char **argv)
{

    try
    {
        std::vector<std::string> cmd(argv, argv + argc);

        std::map<std::string, std::string> m;

        const std::string help{"--help"}, output{"--output"}, output_sh{"-o"},
            help_sh{"-h"}, mainland{"--mainland"}, mainland_sh{"-m"},
            country{"--country"}, country_sh{"-c"}, all{"--all"};

        /////////////////////////////////////////////////////////
        /// USAGE
        /// /////////////////////////////////////////////////////
        if (cmd.size() == 1 || cmd.size() > 5 || cmd.size() == 3)
        {
            std::cerr
                << "Usage: ipcountriesdownloader [OPTION]\n"
                << "Try 'ipcountriesdownloader --help' for more information.\n";
            return 0;
        }

        if (cmd.size() == 2)
        {
            ///////////////////////////////////////////////////
            /// HELP
            /// ///////////////////////////////////////////////
            if (cmd[1] == help || cmd[1] == help_sh)
            {
                std::cout << ipsuip::help_out << std::endl;
                return 0;
            }

            ////////////////////////////////////////////////////
            /// MAINLAND COUNTRY
            /// ////////////////////////////////////////////////
            else if (cmd[1] == mainland || cmd[1] == mainland_sh ||
                     cmd[1] == country || cmd[1] == country_sh)
            {
                if (cmd[1] == mainland || cmd[1] == mainland_sh)
                {
                    m = ipsuip::map_code(ipsuip::mainland_code_data);
                }
                else if (cmd[1] == country || cmd[1] == country_sh)
                {
                    m = ipsuip::map_code(ipsuip::country_code_data);
                }

                ipsuip::print_map(m);

                return 0;
            }

            ////////////////////////////////////////////////////
            ///
            /// ////////////////////////////////////////////////
            else if (cmd[1] == all)
            {
                throw std::runtime_error(
                    "Directory not specified! Use -o OR --output");
            }
            else
            {
                throw std::runtime_error("argument not correct!");
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

            if (cmd[2] == mainland_sh || cmd[2] == mainland)
            {
                m = ipsuip::map_code(ipsuip::mainland_code_data);
                for (const auto &code : ipsuip::codes_mainlands)
                {
                    std::string spath{cmd[4]};
                    if (spath.back() != '/')
                        spath.push_back('/');

                    spath.append(m[code] + "/");

                    ipsuip::run_init(code, spath, m,
                                     ipsuip::TYPEPARSING::CONTINENT);
                }
            }
            else

                if (cmd[2] == country_sh || cmd[2] == country)
            {
                m = ipsuip::map_code(ipsuip::country_code_data);
                for (const auto &code : ipsuip::codes_countries)
                {
                    std::string spath{cmd[4]};
                    if (spath.back() != '/')
                        spath.push_back('/');

                    spath.append(m[code] + "/");

                    ipsuip::run_init(code, spath, m,
                                     ipsuip::TYPEPARSING::COUNTRY);
                }
            }

            return 0;
        }

        //////////////////////////////////////////////////////////////
        ///   MAINLAND COUNTRY
        /// //////////////////////////////////////////////////////////
        else if ((cmd.size() == 5 && cmd[3] == output_sh) || (cmd.size() == 5 && cmd[3] == output)) {
            Timer timer;

            if ((cmd[1] == mainland && ipsuip::codes_mainlands.contains(cmd[2]))
                || (cmd[1] == mainland_sh && ipsuip::codes_mainlands.contains(cmd[2]))) {
                m = ipsuip::map_code(ipsuip::mainland_code_data);

                run_init(cmd[2], cmd[4], m, ipsuip::TYPEPARSING::CONTINENT);
            } else if ((cmd[1] == country && ipsuip::codes_countries.contains(cmd[2]))
                       || (cmd[1] == country_sh && ipsuip::codes_countries.contains(cmd[2]))) {
                m = ipsuip::map_code(ipsuip::country_code_data);

                run_init(cmd[2], cmd[4], m, ipsuip::TYPEPARSING::COUNTRY);
            } else {
                throw std::runtime_error(cmd[2] +
                                         " this is the wrong argument!");
            }

            return 0;
        }

        ////////////////////////////////////////////////////////////////////
        ///
        /// ////////////////////////////////////////////////////////////////
        else {
            throw std::runtime_error("Argument not valid!");
        }

        return 0;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
