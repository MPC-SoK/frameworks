cmake_minimum_required (VERSION 3.0)
project (emp-docker-test)
set(NAME "emp-docker-test")

find_path(CMAKE_FOLDER NAMES cmake/emp-tool-config.cmake)
include(${CMAKE_FOLDER}/cmake/emp-base.cmake)
include(${CMAKE_FOLDER}/cmake/enable_rdseed.cmake)
# include(${CMAKE_FOLDER}/cmake/enable_float.cmake)

find_package(emp-sh2pc REQUIRED)
include_directories(${EMP-SH2PC_INCLUDE_DIRS})

find_package(emp-ag2pc REQUIRED)
include_directories(${EMP-AG2PC_INCLUDE_DIRS})

enable_testing()
add_subdirectory(test)