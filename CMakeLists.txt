cmake_minimum_required(VERSION 2.8.10)

project(printnow-common)

file(GLOB CPP_FILES src/*.cpp)

set(INCLUDES_DIR    ${PROJECT_SOURCE_DIR}/src
                    ${Boost_INCLUDE_DIRS}
                    ${CMAKE_INSTALL_PREFIX}/include)

include_directories(${INCLUDES_DIR})
link_directories(${LINK_DIRECTORIES}
                    ${CMAKE_INSTALL_PREFIX}/lib
                    ${CMAKE_INSTALL_PREFIX}/lib64 )
                    
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(${PROJECT_NAME} SHARED ${CPP_FILES} src/CriticalHandleSignal.h)

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${PROJECT_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)
                      

add_dependencies(${PROJECT_NAME} jsoncpp_)


INSTALL ( DIRECTORY src/
  DESTINATION include/
  FILES_MATCHING PATTERN "*.h")

install(TARGETS ${PROJECT_NAME} DESTINATION lib)

# Expose B's public includes (including Boost transitively) to other
# subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${INCLUDES_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
set(${PROJECT_NAME}_LIBRARY_DIRS
                    ${CMAKE_INSTALL_PREFIX}/lib
                    ${CMAKE_INSTALL_PREFIX}/lib64
    CACHE INTERNAL "${PROJECT_NAME}: Library Directories" FORCE)
        
