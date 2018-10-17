
add_executable(mult3_test mult3_test.cpp common/mult3.cpp)
target_link_libraries(mult3_test ABY::aby ENCRYPTO_utils::encrypto_utils)
