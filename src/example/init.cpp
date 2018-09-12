#include "scope/init/init.hpp"
#include "scope/init/flags.hpp"
#include "scope/utils/utils.hpp"
#include "scope/utils/version.hpp"

#include "config.hpp"


// Declare a new flag
DECLARE_FLAG_bool(example);
DEFINE_FLAG_bool(example, false, "an example flag");

SCOPE_REGISTER_OPTS(
    clara::Opt(FLAG(example))["-e1"]("example flag (from Example|Scope)"),
    clara::Opt(FLAG(example))["-e2"]("another flag (from Example|Scope)")
);

int example_init() {
    
    // Do something with some command line flags
    // parse(argc, argv);
    if (FLAG(version)) {
        // Print a version string
        // These values are defined in example_scope/config.hpp.in
        std::cout << version(SCOPE_PROJECT_NAME,
                             SCOPE_VERSION,
                             SCOPE_GIT_REFSPEC,
                             SCOPE_GIT_HASH,
                             SCOPE_GIT_LOCAL_CHANGES) << std::endl;

        // return 0 so that the Scope init infrastructure continues
        return 0;
    }

    // Do some other initialization
    LOG(info, "Running the example benchmark init hook");

    // Anything but 0 will cause Scope's init infrastructure to exit with this code
    return 0;
}

SCOPE_REGISTER_INIT(example_init);

