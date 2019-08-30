#ifndef DATETIME_H
#define DATETIME_H
#include <chrono>
#include <string>
#include <istream>
#include <ostream>

typedef std::chrono::time_point<std::chrono::system_clock> datetime;

std::string to_string(const datetime& dt, const char* format="%Y-%m-%d %H:%M:%S");
datetime stodt(const std::string& date, const char* format="%Y-%m-%d %H:%M:%S");
std::istream& operator >> (std::istream& strean, datetime& dt);
std::ostream& operator << (std::ostream& strean, datetime& dt);

#endif // DATETIME_H
