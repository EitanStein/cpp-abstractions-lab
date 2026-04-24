cmake_minimum_required(VERSION 3.28) 
project(CPP-ABSTRACTIONS-LAB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# include(FetchContent)

# include(CTest)
# enable_testing()
# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        v3.5.2
# )
# FetchContent_MakeAvailable(Catch2)

# FetchContent_Declare(
#   spdlog
#   GIT_REPOSITORY https://github.com/gabime/spdlog.git
#   GIT_TAG v1.16.0 
# )
# FetchContent_MakeAvailable(spdlog)

add_library(cpp_abstractions_lab INTERFACE)
target_include_directories(cpp_abstractions_lab INTERFACE include)

add_executable(optional_demo examples/optional_demo.cpp src/optional.cpp)
target_link_libraries(optional_demo cpp_abstractions_lab)
