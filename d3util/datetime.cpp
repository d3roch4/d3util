#include "datetime.h"
#include <sstream>
#include <iomanip>

std::string to_string(const datetime & dt, const char* format)
{
    const auto& in_time_t = std::chrono::system_clock::to_time_t(dt);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), format);
    return ss.str();
}

datetime stodt(const std::string &dtstr, const char *format)
{
    struct std::tm tm{};
    if(dtstr.size()){
        std::istringstream ss(dtstr);
        ss.imbue(std::locale("pt_BR.utf-8")); // No linux é necessario: locale-gen pt_BR pt_BR.UTF-8 en_US en_US.UTF-8 && dpkg-reconfigure locales
        ss >> std::get_time(&tm, format); // or just %T in this case
    }
    std::time_t time = mktime(&tm);
    return std::chrono::system_clock::from_time_t(time);
}

std::istream &operator >>(std::istream &strean, datetime &dt)
{
    struct std::tm tm{};
    strean.imbue(std::locale(""));
    strean >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S"); // or just %T in this case
    std::time_t time = mktime(&tm);
    dt = std::chrono::system_clock::from_time_t(time);
    return strean;
}

std::ostream &operator >>(std::ostream &strean, datetime &dt)
{
    strean << to_string(dt);
    return strean;
}
