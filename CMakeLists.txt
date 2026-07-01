cmake_minimum_required(VERSION 3.28) 
project(CPP-ABSTRACTIONS-LAB)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




add_library(cpp_abstractions_lab INTERFACE)
target_include_directories(cpp_abstractions_lab INTERFACE include)

add_executable(optional_demo examples/optional_demo.cpp)
target_link_libraries(optional_demo cpp_abstractions_lab)

add_executable(variant_demo examples/variant_demo.cpp)
target_link_libraries(optional_demo cpp_abstractions_lab)

add_executable(function_demo examples/function_demo.cpp)
target_link_libraries(function_demo cpp_abstractions_lab)
