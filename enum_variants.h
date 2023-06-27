#pragma once
#include <string>

namespace ipsuip {

enum class TYPEPARSING { CONTINENT, COUNTRY };

// enum class VARIANT_VECTOR { CIDR, RANGE, ALL };

enum class VARIANT_WORK {
    HELP,
    OUTPUT,
    OUTPUT_SH,
    HELP_SH,
    MAINLAND,
    MAINLAND_SH,
    COUNTRY,
    COUNTRY_SH,
    ALL
};

//const std::string check_variant_work(const VARIANT_WORK &variant)
//{
//    switch (variant) {
//    case VARIANT_WORK::ALL:
//        return std::string("--all");
//    //    break;
//    case VARIANT_WORK::HELP:
//        return std::string("--help");
//    //    break;
//    case VARIANT_WORK::OUTPUT:
//        return std::string("--output");
//    //    break;
//    case VARIANT_WORK::OUTPUT_SH:
//        return std::string("-o");
//    //    break;
//    case VARIANT_WORK::HELP_SH:
//        return std::string("-h");
//    //    break;
//    case VARIANT_WORK::MAINLAND:
//        return std::string("--mainland");
//    //    break;
//    case VARIANT_WORK::MAINLAND_SH:
//        return std::string("-m");
//    //    break;
//    case VARIANT_WORK::COUNTRY:
//        return std::string("--country");
//    //    break;
//    case VARIANT_WORK::COUNTRY_SH:
//        return std::string("-c");
//    //    break;
//    default:
//        return std::string();
//        //    break;
//    }
//    return std::string();
//}

} // namespace ipsuip
