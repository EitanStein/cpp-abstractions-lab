#include "cpp_version_lab/cpp11/auto_testing.hpp"
#include "cpp_version_lab/cpp11/decltype_testing.hpp"
#include "cpp_version_lab/cpp11/brace_init_testing.hpp"
#include "cpp_version_lab/cpp11/init_list_testing.hpp"
#include "cpp_version_lab/cpp11/explicit_testing.hpp"


int main(){
    testing_auto_deduction();
    decltype_demo();
    brace_init_demo();
    // initialization_list_demo();
    // explicit_lab();
    return 0;
}