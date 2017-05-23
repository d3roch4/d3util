cmake_minimum_required(VERSION 2.8.10)

project(d3util)

file(GLOB CPP_FILES src/*.cpp)

set(INCLUDES_DIR    ${PROJECT_SOURCE_DIR}/src)

include_directories(${INCLUDES_DIR})
link_directories(${LINK_DIRECTORIES})
                    
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#add_library(${PROJECT_NAME} ${CPP_FILES})

# Required on Unix OS family to be able to be linked into shared libraries.
#set_target_properties(${PROJECT_NAME}
#                      PROPERTIES POSITION_INDEPENDENT_CODE ON)
                      

INSTALL ( DIRECTORY src/
  DESTINATION include/
  FILES_MATCHING PATTERN "*.hpp")

install(TARGETS ${PROJECT_NAME} DESTINATION lib)

set(${PROJECT_NAME}_INCLUDE_DIRS ${INCLUDES_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
        
