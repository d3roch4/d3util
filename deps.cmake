include(FetchContent)

FetchContent_Declare (mor
        GIT_REPOSITORY "https://github.com/d3roch4/mor.git"
        )
FetchContent_GetProperties(mor)
FetchContent_Populate(mor)
add_subdirectory(${mor_SOURCE_DIR} ${mor_BINARY_DIR} EXCLUDE_FROM_ALL)

FetchContent_Declare (jsoncpp
        GIT_REPOSITORY "https://github.com/open-source-parsers/jsoncpp.git"
        )
FetchContent_GetProperties(jsoncpp)
FetchContent_Populate(jsoncpp)
add_subdirectory(${jsoncpp_SOURCE_DIR} ${jsoncpp_BINARY_DIR} EXCLUDE_FROM_ALL)

set(BOOST_INCLUDE_LIBRARIES system filesystem log log_setup stacktrace)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.80.0
)
FetchContent_MakeAvailable(Boost)

