# Example|Scope

This is an example benchmark plugin for the [SCOPE](github.com/rai-project/scope) benchmark project.
It most be integrated with SCOPE to build.

## Quickstart

Download latest Example|Scope and create a new_scope.

```
curl -L https://github.com/c3sr/example_scope/archive/master.zip -o master.zip
unzip master.zip
rm master.zip
mv example_scope-master new_scope
```

## Structure

```
example_scope
├── CMakeLists.txt
├── docs
│   └── example_benchmark_class.md
├── LICENCE
├── NOTICE
├── README.md
└── src
    ├── config.hpp.in
    ├── example
    │   ├── example.cpp
    │   ├── init.cpp
    │   └── sugar.cmake
    └── sugar.cmake
```

### `CMakeLists.txt`

Example|Scope will be included in SCOPE with CMake `add_subdirectory`, and this `CMakeLists.txt` is filled accordingly.
CMake 3.12+ is needed for proper object library support.

It should do the following things:
* Use `project` to define a scope name and version.
This is used in config.hpp.in and `configure_file` to help create a version string, and also affect messages printed with `scope_status`.
```cmake
project(Example|Scope LANGUAGES CXX VERSION 1.0.0)
```
* Use [Sugar](https://github.com/ruslo/sugar) to `sugar_include` the plugin sources.
Scope provides a python script for generating `sugar.cmake` files.
Once the plugin is added to scope as a submodule (see below), it can be invoked like this whenever source files are added or moved in the plugin:

        $ scope/tools/generate_sugar_files.py --top example_scope/src --var example

This will cause `example_SOURCES` and `example_CUDA_SOURCES` to be defined.
These are most likely the variables that should be expanded when using `add_library` in the plugin `CMakeLists.txt`.
```cmake
sugar_include(src)
```
* Define a CMake [object library](https://cmake.org/cmake/help/latest/command/add_library.html#id4). For example:
```cmake
add_library(example_scope OBJECT ${example_SOURCES} ${example_CUDA_SOURCES})
```
* Add includes and library linking for utilities provided through SCOPE:
```cmake
target_include_scope_directories(example_scope)
target_link_scope_libraries(example_scope)
```
* link any other required libraries with the PUBLIC keyword so that Scope is also linked with them
```cmake
target_link_libraries(example_scope PUBLIC required-library)
```
* discover certain things about the git repository.
This is used to help generate the version string.
```cmake
git_get_head_revision(GIT_REFSPEC GIT_HASH)
git_local_changes(GIT_LOCAL_CHANGES)
```
* use CMake `configure_file` to generate `example_scope/src/config.hpp`
```cmake
configure_file (
    "${PROJECT_SOURCE_DIR}/src/config.hpp.in"
    "${PROJECT_BINARY_DIR}/src/config.hpp"
)
```
* Include the location of the generated `config.hpp` file.
Also include the `src` directory.
```cmake
target_include_directories(example_scope PRIVATE
    ${PROJECT_BINARY_DIR}/src
    src
)
```

It can also do any other CMake things, like:
* find any required packages needed by the scope

```cmake
find_package(required-library)
```

### `docs`

The `docs` folder should describe all of the benchmarks created by the scope.

### `LICENSE` and `NOTICE`

Example|Scope is licensed under Apache 2.0.
* You must retain the original copyright.
* You must include the full text of the license in the modified software.
* You must state any significant changes you make to the software.
* You must include `NOTICE` if you distribute, and you may append to `NOTICE`.

*disclaimer: no information in this readme is legal advice*

### README.md

The readme should describe the objective of the plugin, the contributors of the scope, and how to cite the scope.

### `src`

All the source files for the benchmarks should be in `src`.
The organization within `src` is up to the developer.

## Adding the plugin to SCOPE

If you have push access to SCOPE, go ahead and add it.
Otherwise, you can submit a PR.

First, this scope should be added to SCOPE as a submodule.
Add with https so anyone can clone.

    cd scope
    git submodule add https://github.com/c3sr/example_scope.git

Then, the [SCOPE CMakeLists.txt](https://github.com/rai-project/scope/blob/master/CMakeLists.txt) should be modified to load this plugin.

An option to enable your scope should be added near the beginning of the CMakeLists.txt file:

```cmake
option(ENABLE_EXAMPLE "Include Example|Scope (github.com/c3sr/example_scope)" OFF)
```

A snippet of code to add your scope to the build should be added further down, after the main scope `add_executable(...)`.

```cmake
if (ENABLE_EXAMPLE)
  scope_status("Enabling Example|Scope")
  add_subdirectory(${SRC_TOP_DIR}/example_scope)
  target_link_libraries(scope example_scope)
endif(ENABLE_EXAMPLE)
```

## SCOPE Utilities

The plugin may (should) make use of utilities provided by Scope in scope.
Those utilities can be included with `#include scope/utils/...`

## SCOPE Initialization Hooks

SCOPE exposes initialization as part of the life cycle.
This happens in [src/example/init.cpp](src/example/init.cpp).
The two macros `SCOPE_REGISTER_BEFORE_INIT` and `SCOPE_REGISTER_INIT` allow a scope to provide SCOPE with a `void(*)()` and `int (*)()` functions, respectively, that are invoked during the BeforeInit and Init lifecycle stages.


## SCOPE Command Line Options

Scopes may also register Clara `clara::Opt`s to describe command line options that they look for.
This may be done statically with the `SCOPE_REGISTER_OPT` macro, or during the BeforeInit hook using `RegisterOpt`.
Flag variables can be declared with the `DECLARE_FLAG_...` and `DEFINE_FLAG_...` family of macros exposed in [scope/src/scope/utils/commandlineflags.hpp]().
An example of this usage is in in [src/example/init.cpp](src/example/init.cpp).


## SCOPE Version String

A scope should provide SCOPE with a version string to print when the user passes `--version` on the command line.
This is done by using `RegisterVersion` during the BeforeInit hook.

## Citation

Please cite the following when referring to this work:

## Contributors

* [Carl Pearson](mailto:pearson@illinois.edu)