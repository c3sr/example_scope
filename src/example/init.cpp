#include "scope/init/init.hpp"
#include "scope/init/flags.hpp"
#include "scope/utils/utils.hpp"
#include "example/version.hpp"

// static void parse(int argc, char  **argv) {
//     for (int i = 1; i < argc; ++i) {
//         if (std::string("--version") == std::string(argv[i])) {
//             version = true;
//         }
//     }
// }

int example_init(int argc, char *const * argv) {
    
    // Do something with some command line flags
    // parse(argc, argv);
    if (FLAG(version)) {
        // Print a version string (this is not a good version string)
        std::cout << SCOPE_PROJECT_NAME << " " << example_scope::version() << std::endl;

        // return 0 so that the Scope init infrastructure continues
        return 0;
    }

    // Do some other initialization
    LOG(info, "Running the example benchmark init hook");

    // Anything but 0 will cause Scope's init infrastructure to exit with this code
    return 0;
}

SCOPE_INIT(example_init);