add_executable(innerprod_test innerproduct_test.cpp common/innerproduct.cpp)
target_link_libraries(innerprod_test ABY::aby ENCRYPTO_utils::encrypto_utils)
