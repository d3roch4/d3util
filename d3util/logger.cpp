#include "logger.h"

void init_logger(const std::string& prefixFile, boost::log::trivial::severity_level severity)
{
//    auto format = boost::log::keywords::format = "[%TimeStamp%]: %Message%";

    boost::log::add_console_log(
        std::clog,
        boost::log::keywords::auto_flush = true
//        format
    );
    boost::log::add_file_log
    (
        boost::log::keywords::auto_flush = true,
        boost::log::keywords::file_name = prefixFile+"_%N.log",
        boost::log::keywords::rotation_size = 10 * 1024,
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0)
//        format
    );
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::trace
    );
}
