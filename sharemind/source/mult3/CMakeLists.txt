# Sharemind MPC example programs
# Copyright (C) 2018 Marcella Hastings
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(STANDALONEDEMO)

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

ADD_COMPILE_OPTIONS(
  "-std=c++11" "-Wall" "-Wextra" "-O2"
  "$<$<NOT:$<STREQUAL:$<CONFIGURATION>,Release>>:-ggdb>"
  "$<$<NOT:$<STREQUAL:$<CONFIGURATION>,Release>>:-fno-omit-frame-pointer>"
  "$<$<STREQUAL:$<CONFIGURATION>,Release>:-DNDEBUG>"
  "$<$<STREQUAL:$<CONFIGURATION>,Release>:-fomit-frame-pointer>"
)

SET(Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE(Boost COMPONENTS program_options system REQUIRED)
FIND_PACKAGE(LogHard REQUIRED)
FIND_PACKAGE(SharemindLibController REQUIRED)
FIND_PACKAGE(SharemindLibIController REQUIRED)

INCLUDE_DIRECTORIES(
    ${Boost_INCLUDE_DIRS}
    ${LogHard_INCLUDE_DIRS}
    ${SharemindLibController_INCLUDE_DIRS}
    ${SharemindLibIController_INCLUDE_DIRS}
)

ADD_DEFINITIONS(
    ${LogHard_DEFINITIONS}
    ${SharemindLibController_DEFINITIONS}
    ${SharemindLibIController_DEFINITIONS}
    "-D__STDC_LIMIT_MACROS"
)

SET(STANDALONEDEMO_LIBRARIES
    ${Boost_LIBRARIES}
    ${LogHard_LIBRARIES}
    ${SharemindLibController_LIBRARIES}
    ${SharemindLibIController_LIBRARIES}
)

FILE(GLOB_RECURSE STANDALONEDEMO_SECREC "${CMAKE_CURRENT_SOURCE_DIR}/secrec/*.sc")

SET(STANDALONEDEMO_FILES ${STANDALONEDEMO_SECREC})

ADD_CUSTOM_TARGET("include_StandaloneDemo_Files_in_IDE"
                  SOURCES ${STANDALONEDEMO_FILES})

ADD_EXECUTABLE(mult3 src/mult3.cpp)
TARGET_LINK_LIBRARIES(mult3 ${STANDALONEDEMO_LIBRARIES})
INSTALL(TARGETS mult3 RUNTIME DESTINATION "bin")
