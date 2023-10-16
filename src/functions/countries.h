#pragma once
#include <set>
#include <string>
#include <vector>

namespace ipsuip
{

inline std::string help_out
    = "Usage: ipcountriesdownloader [MAINLANG/COUNTRY] [PATHTOSAVE]\n"
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

std::set<std::string> codes_mainlands{"AF", "AN", "AS", "EU",
                                      "NA", "OC", "SA", "ZZ"};

std::set<std::string> codes_countries{
    "AF", "AL", "DZ", "AS", "AD", "AO", "AI", "AQ", "AG", "AR", "AM", "AW",
    "AU", "AT", "AZ", "BS", "BH", "BD", "BB", "BY", "BE", "BZ", "BJ", "BM",
    "BT", "BO", "BA", "BW", "BR", "IO", "VG", "BN", "BG", "BF", "BI", "KH",
    "CM", "CA", "CV", "KY", "CF", "TD", "CL", "CN", "CX", "CC", "CO", "KM",
    "CK", "CR", "HR", "CU", "CW", "CY", "CZ", "CD", "DK", "DJ", "DM", "DO",
    "TL", "EC", "EG", "SV", "GQ", "ER", "EE", "ET", "FK", "FO", "FJ", "FI",
    "FR", "PF", "GA", "GM", "GE", "DE", "GH", "GI", "GR", "GL", "GD", "GU",
    "GT", "GG", "GN", "GW", "GY", "HT", "HN", "HK", "HU", "IS", "IN", "ID",
    "IR", "IQ", "IE", "IM", "IL", "IT", "CI", "JM", "JP", "JE", "JO", "KZ",
    "KE", "KI", "XK", "KW", "KG", "LA", "LV", "LB", "LS", "LR", "LY", "LI",
    "LT", "LU", "MO", "MK", "MG", "MW", "MY", "MV", "ML", "MT", "MH", "MR",
    "MU", "YT", "MX", "FM", "MD", "MC", "MN", "ME", "MS", "MA", "MZ", "MM",
    "NA", "NR", "NP", "NL", "AN", "NC", "NZ", "NI", "NE", "NG", "NU", "KP",
    "MP", "NO", "OM", "PK", "PW", "PS", "PA", "PG", "PY", "PE", "PH", "PN",
    "PL", "PT", "PR", "QA", "CG", "RE", "RO", "RU", "RW", "BL", "SH", "KN",
    "LC", "MF", "PM", "VC", "WS", "SM", "ST", "SA", "SN", "RS", "SC", "SL",
    "SG", "SX", "SK", "SI", "SB", "SO", "ZA", "KR", "SS", "ES", "LK", "SD",
    "SR", "SJ", "SZ", "SE", "CH", "SY", "TW", "TJ", "TZ", "TH", "TG", "TK",
    "TO", "TT", "TN", "TR", "TM", "TC", "TV", "US", "UG", "UA", "AE", "GB",
    "US", "UY", "UZ", "VU", "VA", "VE", "VN", "WF", "EH", "YE", "ZM", "ZW"};

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

std::vector<std::string> country_code_data{
    "Afghanistan", "AF", "Albania", "AL", "Algeria", "DZ", "American_Samoa",
    "AS", "Andorra", "AD", "Angola", "AO", "Anguilla", "AI", "Antarctica", "AQ",
    "Antigua_and_Barbuda", "AG", "Argentina", "AR", "Armenia", "AM", "Aruba",
    "AW", "Australia", "AU", "Austria", "AT", "Azerbaijan", "AZ", "Bahamas",
    "BS", "Bahrain", "BH", "Bangladesh", "BD", "Barbados", "BB", "Belarus",
    "BY", "Belgium", "BE", "Belize", "BZ", "Benin", "BJ", "Bermuda", "BM",
    "Bhutan", "BT", "Bolivia", "BO", "Bosnia_and_Herzegovina", "BA", "Botswana",
    "BW", "Brazil", "BR", "British_Indian_Ocean_Territory", "IO",
    "British_Virgin_Islands", "VG", "Brunei", "BN", "Bulgaria", "BG",
    "Burkina_Faso", "BF", "Burundi", "BI", "Cambodia", "KH", "Cameroon", "CM",
    "Canada", "CA", "Cape_Verde", "CV", "Cayman_Islands", "KY",
    "Central_African_Republic", "CF", "Chad", "TD", "Chile", "CL", "China",
    "CN",
    //"Christmas_Island", "CX",
    "Cocos_Islands", "CC", "Colombia", "CO", "Comoros", "KM", "Cook_Islands",
    "CK", "Costa_Rica", "CR", "Croatia", "HR", "Cuba", "CU", "Curacao", "CW",
    "Cyprus", "CY", "Czech_Republic", "CZ", "Democratic_Republic_of_the_Congo",
    "CD", "Denmark", "DK", "Djibouti", "DJ", "Dominica", "DM",
    "Dominican_Republic", "DO", "East_Timor", "TL", "Ecuador", "EC", "Egypt",
    "EG", "El_Salvador", "SV", "Equatorial_Guinea", "GQ", "Eritrea", "ER",
    "Estonia", "EE", "Ethiopia", "ET", "Falkland_Islands", "FK",
    "Faroe_Islands", "FO", "Fiji", "FJ", "Finland", "FI", "France", "FR",
    "French_Polynesia", "PF", "Gabon", "GA", "Gambia", "GM", "Georgia", "GE",
    "Germany", "DE", "Ghana", "GH", "Gibraltar", "GI", "Greece", "GR",
    "Greenland", "GL", "Grenada", "GD", "Guam", "GU", "Guatemala", "GT",
    "Guernsey", "GG", "Guinea", "GN", "Guinea_Bissau", "GW", "Guyana", "GY",
    "Haiti", "HT", "Honduras", "HN", "Hong_Kong", "HK", "Hungary", "HU",
    "Iceland", "IS", "India", "IN", "Indonesia", "ID", "Iran", "IR", "Iraq",
    "IQ", "Ireland", "IE", "Isle_of_Man", "IM", "Israel", "IL", "Italy", "IT",
    "Ivory_Coast", "CI", "Jamaica", "JM", "Japan", "JP", "Jersey", "JE",
    "Jordan", "JO", "Kazakhstan", "KZ", "Kenya", "KE", "Kiribati", "KI",
    //"Kosovo", "XK",
    "Kuwait", "KW", "Kyrgyzstan", "KG", "Laos", "LA", "Latvia", "LV", "Lebanon",
    "LB", "Lesotho", "LS", "Liberia", "LR", "Libya", "LY", "Liechtenstein",
    "LI", "Lithuania", "LT", "Luxembourg", "LU", "Macau", "MO", "Macedonia",
    "MK", "Madagascar", "MG", "Malawi", "MW", "Malaysia", "MY", "Maldives",
    "MV", "Mali", "ML", "Malta", "MT", "Marshall_Islands", "MH", "Mauritania",
    "MR", "Mauritius", "MU", "Mayotte", "YT", "Mexico", "MX", "Micronesia",
    "FM", "Moldova", "MD", "Monaco", "MC", "Mongolia", "MN", "Montenegro", "ME",
    "Montserrat", "MS", "Morocco", "MA", "Mozambique", "MZ", "Myanmar", "MM",
    "Namibia", "NA", "Nauru", "NR", "Nepal", "NP", "Netherlands", "NL",
    //"Netherlands_Antilles", "AN",
    "New_Caledonia", "NC", "New_Zealand", "NZ", "Nicaragua", "NI", "Niger",
    "NE", "Nigeria", "NG", "Niue", "NU", "North_Korea", "KP",
    "Northern_Mariana_Islands", "MP", "Norway", "NO", "Oman", "OM", "Pakistan",
    "PK", "Palau", "PW", "Palestine", "PS", "Panama", "PA", "Papua_New_Guinea",
    "PG", "Paraguay", "PY", "Peru", "PE", "Philippines", "PH",
    //"Pitcairn", "PN",
    "Poland", "PL", "Portugal", "PT", "Puerto_Rico", "PR", "Qatar", "QA",
    "Republic_of_the_Congo", "CG", "Reunion", "RE", "Romania", "RO", "Russia",
    "RU", "Rwanda", "RW", "Saint_Barthelemy", "BL",
    //"Saint_Helena", "SH",
    "Saint_Kitts_and_Nevis", "KN", "Saint_Lucia", "LC", "Saint_Martin", "MF",
    "Saint_Pierre_and_Miquelon", "PM", "Saint_Vincent_and_the_Grenadines", "VC",
    "Samoa", "WS", "San_Marino", "SM", "Sao_Tome_and_Principe", "ST",
    "Saudi_Arabia", "SA", "Senegal", "SN", "Serbia", "RS", "Seychelles", "SC",
    "Sierra_Leone", "SL", "Singapore", "SG", "Sint_Maarten", "SX", "Slovakia",
    "SK", "Slovenia", "SI", "Solomon_Islands", "SB", "Somalia", "SO",
    "South_Africa", "ZA", "South_Korea", "KR", "South_Sudan", "SS", "Spain",
    "ES", "Sri_Lanka", "LK", "Sudan", "SD", "Suriname", "SR",
    //"Svalbard_and_Jan_Mayen", "SJ",
    "Swaziland", "SZ", "Sweden", "SE", "Switzerland", "CH", "Syria", "SY",
    "Taiwan", "TW", "Tajikistan", "TJ", "Tanzania", "TZ", "Thailand", "TH",
    "Togo", "TG", "Tokelau", "TK", "Tonga", "TO", "Trinidad_and_Tobago", "TT",
    "Tunisia", "TN", "Turkey", "TR", "Turkmenistan", "TM",
    "Turks_and_Caicos_Islands", "TC", "Tuvalu", "TV", "U.S._Virgin_Islands",
    "VI", "Uganda", "UG", "Ukraine", "UA", "United_Arab_Emirates", "AE",
    "United_Kingdom", "GB", "United_States", "US", "Uruguay", "UY",
    "Uzbekistan", "UZ", "Vanuatu", "VU", "Vatican", "VA", "Venezuela", "VE",
    "Vietnam", "VN", "Wallis_and_Futuna", "WF",
    //"Western_Sahara", "EH",
    "Yemen", "YE", "Zambia", "ZM", "Zimbabwe", "ZW"};
} // namespace ipsuip
