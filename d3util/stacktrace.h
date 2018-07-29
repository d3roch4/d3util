#ifndef STACKTRACE_H
#define STACKTRACE_H


#include <signal.h>     // ::signal, ::raise
#include <stdexcept>    // std::logic_error
#include <iostream>     // std::cerr
#include <boost/stacktrace.hpp>
#include <boost/exception/all.hpp>

void backtrace_signal_handler(int signum);
void print_stacktrace_previous_run_crash();

// BOOST_ENABLE_ASSERT_DEBUG_HANDLER is defined for the whole project
namespace boost {
    inline void assertion_failed_msg(char const* expr, char const* msg, char const* function, char const* /*file*/, long /*line*/) {
        std::cerr << "Expression '" << expr << "' is false in function '" << function << "': " << (msg ? msg : "<...>") << ".\n"
            << "Backtrace:\n" << boost::stacktrace::stacktrace() << '\n';
        std::abort();
    }

    inline void assertion_failed(char const* expr, char const* function, char const* file, long line) {
        ::boost::assertion_failed_msg(expr, 0 /*nullptr*/, function, file, line);
    }
} // namespace boost

typedef boost::error_info<struct tag_stacktrace, boost::stacktrace::stacktrace> traced;

template <class E>
void throw_with_trace(const E& e) {
    throw boost::enable_error_info(e)
        << traced(boost::stacktrace::stacktrace());
}

void print_stacktrace(const std::exception& e);

#endif // STACKTRACE_H
