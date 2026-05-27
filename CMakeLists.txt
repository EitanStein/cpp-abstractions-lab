cmake_minimum_required(VERSION 3.28) 
project(CPP-ABSTRACTIONS-LAB)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# include(FetchContent)

# include(CTest)
# enable_testing()
# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        6ee0826dcae55ed1e06b2c5701981221e979e1e6 #3.15.0
# )
# FetchContent_MakeAvailable(Catch2)

# FetchContent_Declare(
#   spdlog
#   GIT_REPOSITORY https://github.com/gabime/spdlog.git
#   GIT_TAG        486b55554f11c9cccc913e11a87085b2a91f706f #1.16.0
# )
# FetchContent_MakeAvailable(spdlog)

add_library(cpp_abstractions_lab INTERFACE)
target_include_directories(cpp_abstractions_lab INTERFACE include)

add_executable(optional_demo examples/optional_demo.cpp)
target_link_libraries(optional_demo cpp_abstractions_lab)

add_executable(variant_demo examples/variant_demo.cpp)
target_link_libraries(optional_demo cpp_abstractions_lab)

add_executable(function_demo examples/function_demo.cpp)
target_link_libraries(function_demo cpp_abstractions_lab)
