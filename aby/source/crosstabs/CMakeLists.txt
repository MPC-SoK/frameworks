
add_executable(crosstabs_test crosstabs_test.cpp common/crosstabs.cpp)
target_link_libraries(crosstabs_test ABY::aby ENCRYPTO_utils::encrypto_utils)
