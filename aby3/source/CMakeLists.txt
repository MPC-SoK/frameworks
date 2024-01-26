
#project(samples)

#############################################
#               Build samples.exe           #
#############################################

file(GLOB_RECURSE SRC_SAMPLES ${CMAKE_SOURCE_DIR}/samples/*.cpp)
include_directories(${CMAKE_SOURCE_DIR}/samples/)

add_executable(samples.exe ${SRC_SAMPLES})

target_link_libraries(samples.exe com-psi)
target_link_libraries(samples.exe aby3-ML)
target_link_libraries(samples.exe com-psi_Tests)
target_link_libraries(samples.exe aby3_Tests)
target_link_libraries(samples.exe oc::tests_cryptoTools)
