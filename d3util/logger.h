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
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/console.hpp>

#define  LOG_TRACE   BOOST_LOG_TRIVIAL(trace) << BOOST_CURRENT_FUNCTION << ": "
#define  LOG_DEBUG   BOOST_LOG_TRIVIAL(debug) << BOOST_CURRENT_FUNCTION << ": "
#define  LOG_INFO    BOOST_LOG_TRIVIAL(info)  << ": "
#define  LOG_WARNING BOOST_LOG_TRIVIAL(warning) << BOOST_CURRENT_FUNCTION << ": "
#define  LOG_ERROR   BOOST_LOG_TRIVIAL(error) << BOOST_CURRENT_FUNCTION << ": "
#define  LOG_FATAL   BOOST_LOG_TRIVIAL(fatal) << BOOST_CURRENT_FUNCTION << ": "

void init_logger(const std::string& prefixFile, boost::log::trivial::severity_level severity=boost::log::trivial::severity_level::info);

#endif // LOGGER_H
