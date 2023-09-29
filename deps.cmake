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

find_package(Boost COMPONENTS system filesystem log log_setup stacktrace)
if(NOT Boost_FOUND)
    FetchContent_Declare (boost-cmake
            GIT_REPOSITORY "https://github.com/d3roch4/boost-cmake.git"
            )
    FetchContent_GetProperties(boost-cmake)
    FetchContent_Populate(boost-cmake)
    add_subdirectory(${boost-cmake_SOURCE_DIR} ${boost-cmake_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
