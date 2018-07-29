#ifndef d3LOGGER_H
#define d3LOGGER_H

//////////// LOGGER BOOST //////////////////

#include <boost/log/core/core.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/console.hpp>

#define  LOG_TRACE   BOOST_LOG_TRIVIAL(trace) << BOOST_CURRENT_FUNCTION << ": "
#define  LOG_DEBUG   BOOST_LOG_TRIVIAL(debug) << BOOST_CURRENT_FUNCTION << ": "
#define  LOG_INFO    BOOST_LOG_TRIVIAL(info)  << ": "
#define  LOG_WARNING BOOST_LOG_TRIVIAL(warning) << BOOST_CURRENT_FUNCTION << ": "
#define  LOG_ERROR   BOOST_LOG_TRIVIAL(error) << BOOST_CURRENT_FUNCTION << ": "
#define  LOG_FATAL   BOOST_LOG_TRIVIAL(fatal) << BOOST_CURRENT_FUNCTION << ": "

inline void init_logger(const std::string& prefixFile, boost::log::trivial::severity_level severity=boost::log::trivial::severity_level::info)
{
    auto format = boost::log::keywords::format = (
        boost::log::expressions::stream
        << boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
        << "[" << boost::log::trivial::severity
        << "] " << boost::log::expressions::smessage
    );
    boost::log::add_console_log(
        std::clog,
        boost::log::keywords::auto_flush = true,
        format
    );
    boost::log::add_file_log
    (
        boost::log::keywords::auto_flush = true,
        boost::log::keywords::file_name = prefixFile+"_%N.log",
        boost::log::keywords::rotation_size = 10 * 1024,
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
        format
    );
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::trace
    );
}

#endif // LOGGER_H
