#pragma once
#include <string>

namespace ipsuip {

enum class TYPEPARSING { CONTINENT, COUNTRY };

enum class VARIANT_VECTOR { CIDR, RANGE, ALL };

enum class VARIANT {
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

std::string check_variant(const VARIANT &variant)
{
    switch (variant) {
    case VARIANT::ALL:
        return "--all";
        break;
    case VARIANT::HELP:
        return "--help";
        break;
    case VARIANT::OUTPUT:
        return "--output";
        break;
    case VARIANT::OUTPUT_SH:
        return "-o";
        break;
    case VARIANT::HELP_SH:
        return "-h";
        break;
    case VARIANT::MAINLAND:
        return "--mainland";
        break;
    case VARIANT::MAINLAND_SH:
        return "-m";
        break;
    case VARIANT::COUNTRY:
        return "--country";
        break;
    case VARIANT::COUNTRY_SH:
        return "-c";
        break;
    default:
        break;
    }
}

} // namespace ipsuip
