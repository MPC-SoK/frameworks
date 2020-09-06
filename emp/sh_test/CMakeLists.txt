cmake_minimum_required (VERSION 3.0)
project (emp-docker-test)
set(NAME "emp-docker-test")

find_path(CMAKE_FOLDER NAMES cmake/emp-tool-config.cmake)
include(${CMAKE_FOLDER}/cmake/common.cmake)
include(${CMAKE_FOLDER}/cmake/enable_rdseed.cmake)
include(${CMAKE_FOLDER}/cmake/enable_float.cmake)

find_package(emp-sh2pc REQUIRED)
include_directories(${EMP-SH2PC_INCLUDE_DIRS})

macro (add_test _name)
	add_test_with_lib(${_name} ${EMP-TOOL_LIBRARIES})
endmacro()

add_test(mult3)
add_test(innerprod)
add_test(xtabs)