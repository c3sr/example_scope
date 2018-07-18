#include "scope/init/init.hpp"
#include "scope/utils/utils.hpp"

void example_init(int argc, char **argv) {
    // silence compiler warnings about unused arguments
    (void) argc;
    (void) argv;

    // Do some initialization
    LOG(info, "Running the example benchmark init hook");
}

SCOPE_INIT(example_init);