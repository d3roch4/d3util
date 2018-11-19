#include "logger.h"
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>

void init_logger(const std::string& prefixFile, boost::log::trivial::severity_level severity)
{
//    auto format = boost::log::keywords::format = "[%TimeStamp%]: %Message%";
    namespace expr = boost::log::expressions;

    auto format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%";

    boost::log::add_console_log(
        std::clog
//        boost::log::keywords::format = format
    );
    boost::log::add_file_log
    (
        boost::log::keywords::file_name = prefixFile,
        boost::log::keywords::rotation_size = 10 * 1024
//        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0)
//                boost::log::keywords::format = format
    );
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::trace
    );
}
