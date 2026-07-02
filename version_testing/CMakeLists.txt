

add_executable(cpp11_demo cpp11.cpp)
#target_link_libraries(cpp11_demo cpp_version_lab/cpp11)

target_include_directories(cpp11_demo 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)