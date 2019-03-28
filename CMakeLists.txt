cmake_minimum_required(VERSION 2.8)

project(d3util) # Tools Util

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB CPP_FILES d3util/*.cpp)
file(GLOB HPP_FILES d3util/*.h)

set(Boost_USE_STATIC_LIBS ON)
add_compile_definitions(BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED=1)
find_package(Boost REQUIRED COMPONENTS system filesystem log stacktrace_basic)
include_directories(src ${Boost_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${CPP_FILES} ${HPP_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ./)
target_link_libraries(${PROJECT_NAME} dl ${Boost_LIBRARIES} )

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HPP_FILES} DESTINATION include/${PROJECT_NAME})

include(jsoncpp.cmake)

if(NOT TARGET mor)
    add_subdirectory(../mor mor)
endif()
target_link_libraries(${PROJECT_NAME} mor)

option(BUILD_EXAMPLE "Build example code" OFF)
if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()
