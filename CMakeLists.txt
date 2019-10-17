cmake_minimum_required(VERSION 2.8)

project(d3util) # Tools Util

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB CPP_FILES d3util/*.cpp)
file(GLOB HPP_FILES d3util/*.h)

set(Boost_USE_STATIC_LIBS ON)
add_compile_definitions(BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED=1)
if (WIN32)
    set(STACKTRACE stacktrace_windbg)
else()
    set(STACKTRACE stacktrace_addr2line)
endif ()
set(FETCHCONTENT_SOURCE_DIR_BOOST "C:/Users/andre/workspace/teleentrega-servidor/build/_deps/boost-src")
add_subdirectory(deps/boost-cmake)
#find_package(Boost COMPONENTS system filesystem log log_setup ${STACKTRACE} REQUIRED)
#include_directories(src ${Boost_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${CPP_FILES} ${HPP_FILES}) 
target_include_directories(${PROJECT_NAME} PUBLIC ./)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::filesystem Boost::log Boost::log_setup Boost::stacktrace )

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HPP_FILES} DESTINATION include/${PROJECT_NAME})

if(NOT TARGET mor)
    add_subdirectory(deps/mor mor)
endif()
target_link_libraries(${PROJECT_NAME} mor)

if(NOT TARGET jsoncpp_lib)
    add_subdirectory(deps/jsoncpp jsoncpp)
endif()
target_link_libraries(${PROJECT_NAME} jsoncpp_lib)

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
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "'git submodule update --init' failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
        execute_process(COMMAND ${GIT_EXECUTABLE} pull --recurse-submodules
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "'git pull --recurse-submodules' failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --remote --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "'git submodule update --remote --recursive' failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()