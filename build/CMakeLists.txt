cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)

project(byoo_dbot VERSION 1.0 DESCRIPTION "General purpose discord bot")

# Add local dpp library
find_library(DPP_LIBRARY NAMES dpp "libdpp.a" PATHS ${DPP_ROOT_DIR})
find_path(DPP_INCLUDE Names dpp/dpp.h PATHS ${DPP_ROOT_DIR})

# Add boost library
# find_package(Boost REQUIRED COMPONENTS log system)
# include_directories(${Boost_INCLUDE_DIRS})
# add_definitions(-DBOOST_LOG_DYN_LINK)
# add_definitions(-DBOOST_LOG_USE_CHAR)

# Add project sources
file(GLOB_RECURSE SOURCES "../src/*.cpp")

# Add project include directories
include_directories(../inc)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add cURLpp library
# find_library(CURLPP_LIBRARY curlpp)
# find_path(CURLPP_INCLUDE_DIR curlpp/cURLpp.hpp)
# find_package(CURL REQUIRED)

# Find RapidJSON package
# find_package(RapidJSON REQUIRED)

# Link libraries and include directories
target_link_libraries(${PROJECT_NAME} ${DPP_LIBRARY})
target_include_directories(${PROJECT_NAME} PRIVATE ${DPP_INCLUDE})

# Set the output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../bin")
