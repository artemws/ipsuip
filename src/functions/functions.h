#pragma once
#ifndef FUNCTIONS
#define FUNCTIONS

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

    std::string help_out =
        "Usage: ipcountriesdownloader [MAINLANG/COUNTRY] [PATHTOSAVE]\n"
        "To show this help --help OR -h\n\n"
        "The program downloads the IP addresses of the selected country.\n\n"
        "OPTIONS:\n"
        "-m --mainland   Without arguments prints the mainland-code list to the "
        "console.\n"
        "-c --country    Without arguments prints the country-code list to the "
        "console.\n"
        "-o --output     Directory where you plan to save files with ip "
        "addresses.\n                To avoid errors, the path must contain only "
        "Latin "
        "characters\n"
        "                without spaces, asterisks, pound signs and other command "
        "line characters.\n"
        "--all [-m, -c]  Downloads the entire database of ip addresses of all "
        "countries OR mainlands. Can take a very long time!\n\n"
        "EXAMPLES:\n"
        "Ip addresses of the specified country OR continent will be downloaded to "
        "the specified "
        "folder as text files in RANGE format and CIDR format.\n"
        "1) ipcountriesdownloader -c US -o /home/user/Desktop/\n2) "
        "ipcountriesdownloader "
        "-c "
        "GE "
        "-o ./\n3) ipcountriesdownloader --all -c -o "
        "~/Downloads/CountryIPs/\n4) ipcountriesdownloader -m OC -o "
        "/home/user/Desktop/Oceania\n";

    std::set<std::string> codes_mainlands{"AF", "AN", "AS", "EU", "NA", "OC", "SA", "ZZ"};

    std::set<std::string> codes_countries{
        "AF", "AL", "DZ", "AS", "AD", "AO", "AI", "AQ", "AG", "AR", "AM", "AW", "AU", "AT", "AZ",
        "BS", "BH", "BD", "BB", "BY", "BE", "BZ", "BJ", "BM", "BT", "BO", "BA", "BW", "BR", "IO",
        "VG", "BN", "BG", "BF", "BI", "KH", "CM", "CA", "CV", "KY", "CF", "TD", "CL", "CN", "CX",
        "CC", "CO", "KM", "CK", "CR", "HR", "CU", "CW", "CY", "CZ", "CD", "DK", "DJ", "DM", "DO",
        "TL", "EC", "EG", "SV", "GQ", "ER", "EE", "ET", "FK", "FO", "FJ", "FI", "FR", "PF", "GA",
        "GM", "GE", "DE", "GH", "GI", "GR", "GL", "GD", "GU", "GT", "GG", "GN", "GW", "GY", "HT",
        "HN", "HK", "HU", "IS", "IN", "ID", "IR", "IQ", "IE", "IM", "IL", "IT", "CI", "JM", "JP",
        "JE", "JO", "KZ", "KE", "KI", "XK", "KW", "KG", "LA", "LV", "LB", "LS", "LR", "LY", "LI",
        "LT", "LU", "MO", "MK", "MG", "MW", "MY", "MV", "ML", "MT", "MH", "MR", "MU", "YT", "MX",
        "FM", "MD", "MC", "MN", "ME", "MS", "MA", "MZ", "MM", "NA", "NR", "NP", "NL", "AN", "NC",
        "NZ", "NI", "NE", "NG", "NU", "KP", "MP", "NO", "OM", "PK", "PW", "PS", "PA", "PG", "PY",
        "PE", "PH", "PN", "PL", "PT", "PR", "QA", "CG", "RE", "RO", "RU", "RW", "BL", "SH", "KN",
        "LC", "MF", "PM", "VC", "WS", "SM", "ST", "SA", "SN", "RS", "SC", "SL", "SG", "SX", "SK",
        "SI", "SB", "SO", "ZA", "KR", "SS", "ES", "LK", "SD", "SR", "SJ", "SZ", "SE", "CH", "SY",
        "TW", "TJ", "TZ", "TH", "TG", "TK", "TO", "TT", "TN", "TR", "TM", "TC", "TV", "US", "UG",
        "UA", "AE", "GB", "US", "UY", "UZ", "VU", "VA", "VE", "VN", "WF", "EH", "YE", "ZM", "ZW"};

    std::vector<std::string> mainland_code_data{"Europe",
                                                "EU",
                                                "Africa",
                                                "AF",
                                                "Antarctica",
                                                "AN",
                                                "Asia",
                                                "AS",
                                                "North_america",
                                                "NA",
                                                "Oceania",
                                                "OC",
                                                "South_america",
                                                "SA",
                                                "Unknown_or_unspecified",
                                                "ZZ"};

    std::vector<std::string> country_code_data{"Afghanistan",
                                               "AF",
                                               "Albania",
                                               "AL",
                                               "Algeria",
                                               "DZ",
                                               "American_Samoa",
                                               "AS",
                                               "Andorra",
                                               "AD",
                                               "Angola",
                                               "AO",
                                               "Anguilla",
                                               "AI",
                                               "Antarctica",
                                               "AQ",
                                               "Antigua_and_Barbuda",
                                               "AG",
                                               "Argentina",
                                               "AR",
                                               "Armenia",
                                               "AM",
                                               "Aruba",
                                               "AW",
                                               "Australia",
                                               "AU",
                                               "Austria",
                                               "AT",
                                               "Azerbaijan",
                                               "AZ",
                                               "Bahamas",
                                               "BS",
                                               "Bahrain",
                                               "BH",
                                               "Bangladesh",
                                               "BD",
                                               "Barbados",
                                               "BB",
                                               "Belarus",
                                               "BY",
                                               "Belgium",
                                               "BE",
                                               "Belize",
                                               "BZ",
                                               "Benin",
                                               "BJ",
                                               "Bermuda",
                                               "BM",
                                               "Bhutan",
                                               "BT",
                                               "Bolivia",
                                               "BO",
                                               "Bosnia_and_Herzegovina",
                                               "BA",
                                               "Botswana",
                                               "BW",
                                               "Brazil",
                                               "BR",
                                               "British_Indian_Ocean_Territory",
                                               "IO",
                                               "British_Virgin_Islands",
                                               "VG",
                                               "Brunei",
                                               "BN",
                                               "Bulgaria",
                                               "BG",
                                               "Burkina_Faso",
                                               "BF",
                                               "Burundi",
                                               "BI",
                                               "Cambodia",
                                               "KH",
                                               "Cameroon",
                                               "CM",
                                               "Canada",
                                               "CA",
                                               "Cape_Verde",
                                               "CV",
                                               "Cayman_Islands",
                                               "KY",
                                               "Central_African_Republic",
                                               "CF",
                                               "Chad",
                                               "TD",
                                               "Chile",
                                               "CL",
                                               "China",
                                               "CN",
                                               //"Christmas_Island", "CX",
                                               "Cocos_Islands",
                                               "CC",
                                               "Colombia",
                                               "CO",
                                               "Comoros",
                                               "KM",
                                               "Cook_Islands",
                                               "CK",
                                               "Costa_Rica",
                                               "CR",
                                               "Croatia",
                                               "HR",
                                               "Cuba",
                                               "CU",
                                               "Curacao",
                                               "CW",
                                               "Cyprus",
                                               "CY",
                                               "Czech_Republic",
                                               "CZ",
                                               "Democratic_Republic_of_the_Congo",
                                               "CD",
                                               "Denmark",
                                               "DK",
                                               "Djibouti",
                                               "DJ",
                                               "Dominica",
                                               "DM",
                                               "Dominican_Republic",
                                               "DO",
                                               "East_Timor",
                                               "TL",
                                               "Ecuador",
                                               "EC",
                                               "Egypt",
                                               "EG",
                                               "El_Salvador",
                                               "SV",
                                               "Equatorial_Guinea",
                                               "GQ",
                                               "Eritrea",
                                               "ER",
                                               "Estonia",
                                               "EE",
                                               "Ethiopia",
                                               "ET",
                                               "Falkland_Islands",
                                               "FK",
                                               "Faroe_Islands",
                                               "FO",
                                               "Fiji",
                                               "FJ",
                                               "Finland",
                                               "FI",
                                               "France",
                                               "FR",
                                               "French_Polynesia",
                                               "PF",
                                               "Gabon",
                                               "GA",
                                               "Gambia",
                                               "GM",
                                               "Georgia",
                                               "GE",
                                               "Germany",
                                               "DE",
                                               "Ghana",
                                               "GH",
                                               "Gibraltar",
                                               "GI",
                                               "Greece",
                                               "GR",
                                               "Greenland",
                                               "GL",
                                               "Grenada",
                                               "GD",
                                               "Guam",
                                               "GU",
                                               "Guatemala",
                                               "GT",
                                               "Guernsey",
                                               "GG",
                                               "Guinea",
                                               "GN",
                                               "Guinea_Bissau",
                                               "GW",
                                               "Guyana",
                                               "GY",
                                               "Haiti",
                                               "HT",
                                               "Honduras",
                                               "HN",
                                               "Hong_Kong",
                                               "HK",
                                               "Hungary",
                                               "HU",
                                               "Iceland",
                                               "IS",
                                               "India",
                                               "IN",
                                               "Indonesia",
                                               "ID",
                                               "Iran",
                                               "IR",
                                               "Iraq",
                                               "IQ",
                                               "Ireland",
                                               "IE",
                                               "Isle_of_Man",
                                               "IM",
                                               "Israel",
                                               "IL",
                                               "Italy",
                                               "IT",
                                               "Ivory_Coast",
                                               "CI",
                                               "Jamaica",
                                               "JM",
                                               "Japan",
                                               "JP",
                                               "Jersey",
                                               "JE",
                                               "Jordan",
                                               "JO",
                                               "Kazakhstan",
                                               "KZ",
                                               "Kenya",
                                               "KE",
                                               "Kiribati",
                                               "KI",
                                               //"Kosovo", "XK",
                                               "Kuwait",
                                               "KW",
                                               "Kyrgyzstan",
                                               "KG",
                                               "Laos",
                                               "LA",
                                               "Latvia",
                                               "LV",
                                               "Lebanon",
                                               "LB",
                                               "Lesotho",
                                               "LS",
                                               "Liberia",
                                               "LR",
                                               "Libya",
                                               "LY",
                                               "Liechtenstein",
                                               "LI",
                                               "Lithuania",
                                               "LT",
                                               "Luxembourg",
                                               "LU",
                                               "Macau",
                                               "MO",
                                               "Macedonia",
                                               "MK",
                                               "Madagascar",
                                               "MG",
                                               "Malawi",
                                               "MW",
                                               "Malaysia",
                                               "MY",
                                               "Maldives",
                                               "MV",
                                               "Mali",
                                               "ML",
                                               "Malta",
                                               "MT",
                                               "Marshall_Islands",
                                               "MH",
                                               "Mauritania",
                                               "MR",
                                               "Mauritius",
                                               "MU",
                                               "Mayotte",
                                               "YT",
                                               "Mexico",
                                               "MX",
                                               "Micronesia",
                                               "FM",
                                               "Moldova",
                                               "MD",
                                               "Monaco",
                                               "MC",
                                               "Mongolia",
                                               "MN",
                                               "Montenegro",
                                               "ME",
                                               "Montserrat",
                                               "MS",
                                               "Morocco",
                                               "MA",
                                               "Mozambique",
                                               "MZ",
                                               "Myanmar",
                                               "MM",
                                               "Namibia",
                                               "NA",
                                               "Nauru",
                                               "NR",
                                               "Nepal",
                                               "NP",
                                               "Netherlands",
                                               "NL",
                                               //"Netherlands_Antilles", "AN",
                                               "New_Caledonia",
                                               "NC",
                                               "New_Zealand",
                                               "NZ",
                                               "Nicaragua",
                                               "NI",
                                               "Niger",
                                               "NE",
                                               "Nigeria",
                                               "NG",
                                               "Niue",
                                               "NU",
                                               "North_Korea",
                                               "KP",
                                               "Northern_Mariana_Islands",
                                               "MP",
                                               "Norway",
                                               "NO",
                                               "Oman",
                                               "OM",
                                               "Pakistan",
                                               "PK",
                                               "Palau",
                                               "PW",
                                               "Palestine",
                                               "PS",
                                               "Panama",
                                               "PA",
                                               "Papua_New_Guinea",
                                               "PG",
                                               "Paraguay",
                                               "PY",
                                               "Peru",
                                               "PE",
                                               "Philippines",
                                               "PH",
                                               //"Pitcairn", "PN",
                                               "Poland",
                                               "PL",
                                               "Portugal",
                                               "PT",
                                               "Puerto_Rico",
                                               "PR",
                                               "Qatar",
                                               "QA",
                                               "Republic_of_the_Congo",
                                               "CG",
                                               "Reunion",
                                               "RE",
                                               "Romania",
                                               "RO",
                                               "Russia",
                                               "RU",
                                               "Rwanda",
                                               "RW",
                                               "Saint_Barthelemy",
                                               "BL",
                                               //"Saint_Helena", "SH",
                                               "Saint_Kitts_and_Nevis",
                                               "KN",
                                               "Saint_Lucia",
                                               "LC",
                                               "Saint_Martin",
                                               "MF",
                                               "Saint_Pierre_and_Miquelon",
                                               "PM",
                                               "Saint_Vincent_and_the_Grenadines",
                                               "VC",
                                               "Samoa",
                                               "WS",
                                               "San_Marino",
                                               "SM",
                                               "Sao_Tome_and_Principe",
                                               "ST",
                                               "Saudi_Arabia",
                                               "SA",
                                               "Senegal",
                                               "SN",
                                               "Serbia",
                                               "RS",
                                               "Seychelles",
                                               "SC",
                                               "Sierra_Leone",
                                               "SL",
                                               "Singapore",
                                               "SG",
                                               "Sint_Maarten",
                                               "SX",
                                               "Slovakia",
                                               "SK",
                                               "Slovenia",
                                               "SI",
                                               "Solomon_Islands",
                                               "SB",
                                               "Somalia",
                                               "SO",
                                               "South_Africa",
                                               "ZA",
                                               "South_Korea",
                                               "KR",
                                               "South_Sudan",
                                               "SS",
                                               "Spain",
                                               "ES",
                                               "Sri_Lanka",
                                               "LK",
                                               "Sudan",
                                               "SD",
                                               "Suriname",
                                               "SR",
                                               //"Svalbard_and_Jan_Mayen", "SJ",
                                               "Swaziland",
                                               "SZ",
                                               "Sweden",
                                               "SE",
                                               "Switzerland",
                                               "CH",
                                               "Syria",
                                               "SY",
                                               "Taiwan",
                                               "TW",
                                               "Tajikistan",
                                               "TJ",
                                               "Tanzania",
                                               "TZ",
                                               "Thailand",
                                               "TH",
                                               "Togo",
                                               "TG",
                                               "Tokelau",
                                               "TK",
                                               "Tonga",
                                               "TO",
                                               "Trinidad_and_Tobago",
                                               "TT",
                                               "Tunisia",
                                               "TN",
                                               "Turkey",
                                               "TR",
                                               "Turkmenistan",
                                               "TM",
                                               "Turks_and_Caicos_Islands",
                                               "TC",
                                               "Tuvalu",
                                               "TV",
                                               "U.S._Virgin_Islands",
                                               "VI",
                                               "Uganda",
                                               "UG",
                                               "Ukraine",
                                               "UA",
                                               "United_Arab_Emirates",
                                               "AE",
                                               "United_Kingdom",
                                               "GB",
                                               "United_States",
                                               "US",
                                               "Uruguay",
                                               "UY",
                                               "Uzbekistan",
                                               "UZ",
                                               "Vanuatu",
                                               "VU",
                                               "Vatican",
                                               "VA",
                                               "Venezuela",
                                               "VE",
                                               "Vietnam",
                                               "VN",
                                               "Wallis_and_Futuna",
                                               "WF",
                                               //"Western_Sahara", "EH",
                                               "Yemen",
                                               "YE",
                                               "Zambia",
                                               "ZM",
                                               "Zimbabwe",
                                               "ZW"};

    enum class TYPEPARSING { CONTINENT, COUNTRY };

    inline const std::string get_path(std::string path,
                                      const std::string &code,
                                      std::map<std::string, std::string> m)
    {
        if (path.back() != '/')
            path.push_back('/');

        path.append(m[code] + "/");
        return path;
    }

    struct HumanReadable
    {
        std::uintmax_t size{};

        HumanReadable(std::uintmax_t size)
            : size{size}
        {}

    private:
        friend std::ostream &operator<<(std::ostream &os, ipsuip::HumanReadable hr)
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

    std::map<std::string, std::string> map_code(const std::vector<std::string> &_code)
    {
        std::map<std::string, std::string> _map;

        for (size_t value = 0, key = 1; key < _code.size(); value += 2, key += 2) {
            _map[_code[key]] = _code[value];
        }
        return _map;
    }

    std::map<std::string, std::string> map_code_revers(const std::vector<std::string> &_code)
    {
        std::map<std::string, std::string> _map;

        for (size_t value = 0, key = 1; key < _code.size(); value += 2, key += 2) {
            _map[_code[value]] = _code[key];
        }
        return _map;
    }

    inline void print_map(const std::map<std::string, std::string> &m)
    {
        for (const auto &[key, value] : m)
            std::cout << value << " --> " << key << "\n";
    }

    inline std::vector<std::string> get(const std::string &host, const std::string &target)
    {
        using namespace boost;
        namespace net = boost::asio;

        // The io_context is required for all I/O
        asio::io_context ioc;

        // The SSL context is required, and holds certificates
        asio::ssl::context ctx(asio::ssl::context::tlsv12_client);

        // This holds the root certificate used for verification
        ipsuip::load_root_certificates(ctx);

        // Verify the remote server's certificate
        ctx.set_verify_mode(asio::ssl::verify_peer);

        // These objects perform our I/O
        asio::ip::tcp::resolver resolver(ioc);
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str())) {
            beast::error_code ec{static_cast<int>(::ERR_get_error()),
                                 asio::error::get_ssl_category()};
            throw beast::system_error{ec};
        }

        // Look up the domain name
        auto const results = resolver.resolve(host, "443");

        // Make the connection on the IP address we get from a lookup
        beast::get_lowest_layer(stream).connect(results);

        // Perform the SSL handshake
        stream.handshake(asio::ssl::stream_base::client);

        // Set up an HTTP GET request message
        beast::http::request<beast::http::string_body> req(beast::http::verb::get, target, 11);
        req.set(beast::http::field::host, host);
        req.set(beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        beast::http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;
        std::cout << buffer.max_size() << std::endl;

        // Declare a container to hold the response
        beast::http::response_parser<beast::http::string_body> parser;

        // Allow for an unlimited body size
        boost::optional<std::uint64_t> vv;
        vv.emplace(std::numeric_limits<std::uint64_t>::max);
        parser.body_limit(vv);

        system::error_code ecr;
        //std::size_t bytes =
        beast::http::read(stream, buffer, parser, ecr);

        //std::cout << "bytes: " << bytes << std::endl;
        //std::cout << "Download " << HumanReadable(bytes) << "\n";

        if (ecr) {
            std::cerr << ecr.value() << " " << ecr.what() << std::endl;
            //throw beast::system_error{ecr};
        }

        beast::error_code ec;

        // Gracefully close the stream
        stream.shutdown(ec);
        if (ec == net::error::eof) {
        // Rationale: 'eof' means the connection closed cleanly.
            ec = {};
        }
        if (ec) {
        // Log or throw if desired
            std::cerr << "Shutdown error: " << ec.value() << " " << ec.message() << std::endl;
        // throw beast::system_error{ec};
        }

        std::vector<std::string> v;

        std::stringstream ss(parser.get().body());

        for (std::string temp; std::getline(ss, temp);) {
            v.emplace_back(temp);
        }

        if (!v.empty())
            return v;

        return std::vector<std::string>();
    }

    enum class VAR { PARSING_DATA_S, TO_CIDR_S, TO_RANGE_S };

    void get_parsing_data(const std::vector<std::string>::iterator &first,
                          const std::vector<std::string>::iterator &second,
                          std::vector<std::string> &result);

    template<typename Iterator>
    struct parsing_data_s
    {
        void operator()(Iterator first, Iterator last, std::vector<std::string> &result)
        {
            get_parsing_data(first, last, result);
        }
    };

    void to_cidr(const std::vector<std::string>::iterator &first,
                 const std::vector<std::string>::iterator &second,
                 std::vector<std::string> &result);

    template<typename Iterator>
    struct to_cidr_s
    {
        void operator()(Iterator first, Iterator last, std::vector<std::string> &result)
        {
            to_cidr(first, last, result);
        }
    };

    void to_range(const std::vector<std::string>::iterator &first,
                  const std::vector<std::string>::iterator &second,
                  std::vector<std::string> &result);

    template<typename Iterator>
    struct to_range_s
    {
        void operator()(Iterator first, Iterator last, std::vector<std::string> &result)
        {
            to_range(first, last, result);
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

        unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 4,
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

    inline auto parsing_site(const std::string &code, const TYPEPARSING &TYPE)
    {
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
        return v2; // Исправлено: раньше возвращался v, должен возвращаться v2 с результатами // Был возвращён вектор v, теперь возвращается v2 - результат парсинга
    }

    inline bool validateIP(const std::string &ip)
    {
        boost::system::error_code ec;
        boost::asio::ip::make_address_v4(ip, ec);

        if (ec)
            return false;
        return true;
    }

    inline void save_to_file(const std::vector<std::string> &v_ip, const std::string &file_name)
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

    inline void run_init(const std::string &code,
                         const std::string &path,
                         std::map<std::string, std::string> _map,
                         const TYPEPARSING &TYPE)
    {
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

        std::cout << "Saved two files --> " + path_.string() + _map[code] + "_RANGE.txt and "
                  << path_.string() + _map[code] + "_CIDR.txt\n";
    }

    void to_range(const std::vector<std::string>::iterator &first,
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

    inline const std::vector<std::string> range_boundaries_to_cidr(const long int &ip_start,
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
        cidrs.emplace_back(boost::asio::ip::address_v4(ip_start).to_string() + "/" + ss.str());

        if (new_ip < ip_end) { // if we're not done, compute more and join everything together
            std::vector<std::string> tmp_cidrs = range_boundaries_to_cidr(new_ip + 1, ip_end);
            cidrs.insert(cidrs.end(), tmp_cidrs.begin(), tmp_cidrs.end());
        }

        return cidrs;
    }

    void to_cidr(const std::vector<std::string>::iterator &first,
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

    // bool read_from_file(std::ifstream &file, const std::string &str);

    void get_parsing_data(const std::vector<std::string>::iterator &first,
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

    struct IP_a
    {
        std::vector<std::string> RANGE;
        std::vector<std::string> CIDR;
    };

} // namespace ipsuip

#endif // FUNCTIONS
