#include "logger.h"
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/shared_ptr.hpp>

void init_logger(const std::string& prefixFile, boost::log::trivial::severity_level severity)
{
    auto format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%";
    namespace keywords = boost::log::keywords;
    namespace expr = boost::log::expressions;

    boost::log::add_console_log(
        std::clog,
        keywords::format =
        (
            expr::stream
            //<< std::hex   //To print the LineID in Hexadecimal format
//            << std::setw(8) << std::setfill('0')
            << expr::attr< unsigned int >("LineID")
//            << expr::format_date_time<boost::posix_time::ptime>("TimeStamp","%H:%M:%S.%f")
            << "<" << boost::log::trivial::severity
            << ">" << expr::smessage
        )
    );

    boost::log::add_file_log
    (
        keywords::file_name = prefixFile,  /*< file name pattern >*/
        keywords::rotation_size = 10 * 1024,     /*< rotate files every 1 KiB >*/
        /*< log record format >*/
        keywords::format =
        (
            expr::stream
            //<< std::hex   //To print the LineID in Hexadecimal format
//            << std::setw(8) << std::setfill('0')
            << expr::attr< unsigned int >("LineID")
            << "\t"
//            << expr::format_date_time<boost::posix_time::ptime>("TimeStamp","%H:%M:%S.%f")
            << "\t: <" << boost::log::trivial::severity
            << "> \t" << expr::smessage
        )
    );

//    boost::log::core::get()->set_filter
//    (
//        boost::log::trivial::severity >= severity
//    );
}
