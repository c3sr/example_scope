#include "scope/init/init.hpp"
#include "scope/utils/utils.hpp"

bool version = false;

static void parse(int argc, char  **argv) {
    for (int i = 1; i < argc; ++i) {
        if (std::string("--version") == std::string(argv[i])) {
            version = true;
        }
    }
}

int example_init(int argc, char **argv) {
    
    // Do something with some command line flags
    parse(argc, argv);
    if (version) {
        // Print a version string (this is not a good version string)
        std::cout << "Example|Scope - a Scope project" << std::endl;

        // return 0 so that the Scope init infrastructure continues
        return 0;
    }

    // Do some other initialization
    LOG(info, "Running the example benchmark init hook");

    // Anything but 0 will cause Scope's init infrastructure to exit with this code
    return 0;
}

SCOPE_INIT(example_init);