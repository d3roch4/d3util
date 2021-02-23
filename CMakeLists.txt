cmake_minimum_required(VERSION 3.14)

project(d3util VERSION 1.2.3) # Tools Util

set(CMAKE_CXX_STANDARD 14) # -std=c++14
file(GLOB CPP_FILES d3util/*.cpp)
file(GLOB HPP_FILES d3util/*.h)

set(Boost_USE_STATIC_LIBS ON)
add_compile_definitions(BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED=1)
include(deps.cmake)
include_directories(src)

add_library(${PROJECT_NAME} ${CPP_FILES} ${HPP_FILES}) 
target_include_directories(${PROJECT_NAME} PUBLIC ./)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::system Boost::filesystem
    Boost::log Boost::log_setup Boost::stacktrace_addr2line mor jsoncpp_static
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HPP_FILES} DESTINATION include/${PROJECT_NAME})

option(BUILD_EXAMPLE "Build example code" OFF)
if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        #execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
        #                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        #                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        #if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        #    message(FATAL_ERROR "'git submodule update --init' failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        #endif()
        #execute_process(COMMAND ${GIT_EXECUTABLE} pull --recurse-submodules
        #                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        #                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        #if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        #    message(FATAL_ERROR "'git pull --recurse-submodules' failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        #endif()
        #execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --remote --recursive
        #                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        #                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        #if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        #    message(FATAL_ERROR "'git submodule update --remote --recursive' failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        #endif()
    endif()
endif()
