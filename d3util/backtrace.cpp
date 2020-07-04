#include <d3util/stacktrace.h>
#include <boost/filesystem.hpp>
#define BOOST_STACKTRACE_USE_ADDR2LINE
#define BOOST_STACKTRACE_LINK

void backtrace_signal_handler(int signum) {
    ::signal(signum, SIG_DFL);
    boost::stacktrace::safe_dump_to("./backtrace.dump");
    ::raise(SIGABRT);
}

void print_stacktrace_previous_run_crash(){
    if (boost::filesystem::exists("./backtrace.dump")) {
        // there is a backtrace
        std::ifstream ifs("./backtrace.dump");

        boost::stacktrace::stacktrace st = boost::stacktrace::stacktrace::from_dump(ifs);
        std::cout << "Previous run crashed:\n" << st << std::endl;

        // cleaning up
        ifs.close();
        boost::filesystem::remove("./backtrace.dump");
    }
}

namespace boost { namespace stacktrace {

template <class CharT, class TraitsT, class Allocator>
std::basic_ostream<CharT, TraitsT>& do_stream_st(std::basic_ostream<CharT, TraitsT>& os, const basic_stacktrace<Allocator>& bt) {
    const std::streamsize w = os.width();
    const std::size_t frames = bt.size();
    for (std::size_t i = 0; i < frames; ++i) {
        os.width(2);
        os << i;
        os.width(w);
        os << "# ";
        os << bt[i].name();
        os << '\n';
    }

    return os;
}

}}  // namespace boost::stacktrace

void print_stacktrace(const std::exception& e){
    const boost::stacktrace::stacktrace* st = boost::get_error_info<traced>(e);
    if (st) {
        std::cerr << *st << '\n';
    }
}

#include <stdexcept>    // std::logic_error
#include <iostream>     // std::cerr
#include <boost/stacktrace.hpp>
