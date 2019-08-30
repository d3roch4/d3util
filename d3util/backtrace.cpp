#include <d3util/stacktrace.h>
#include <boost/filesystem.hpp>
#define DBOOST_STACKTRACE_USE_ADDR2LINE

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

void print_stacktrace(const std::exception& e){
    const boost::stacktrace::stacktrace* st = boost::get_error_info<traced>(e);
    if (st) {
        std::cerr << *st << '\n';
    }
}
