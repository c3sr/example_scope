# Example|Scope

This is an example benchmark plugin for the [Scope](github.com/rai-project/scopes) benchmark project.
It most be integrated with Scope to build.

## Quickstart

Download latest Example|Scope

```
curl -L https://github.com/c3sr/example_scope/archive/master.zip -o master.zip
unzip master.zip
mv example_scope-master new_scope
```

## Structure (Required)

```
example_scope
├── CMakeLists.txt
├── docs
│   └── example_benchmark_class.md
├── LICENSE.txt
├── README.md
└── src
    ├── example
    │   ├── example.cpp
    │   ├── init.cpp
    │   └── sugar.cmake
    └── sugar.cmake
```

### `CMakeLists.txt`

The plugin `CMakeLists.txt` should 
* `sugar_include` the plugin sources

```cmake
sugar_include(src)
```

* Define a CMake OBJECT library. For example:

```cmake
add_library(example_scope OBJECT ${example_SOURCES} ${example_CUDA_SOURCES})
```

* find any required packages needed by the plugin

```cmake
find_package(required-library)
```
* link any required libraries with the PUBLIC keyword so that Scope is also linked with them

```cmake
target_link_libraries(example_scope PUBLIC required-library)
```

Scope provides a python script for generating `sugar.cmake` files.
Once the plugin is added to scope as a submodule (see below), it can be invoked like this whenever source files are added or moved in the plugin:

    $ scope/tools/generate_sugar_files.py --top example_scope/src --var example

This will cause `example_SOURCES` and `example_CUDA_SOURCES` to be defined.
These are most likely the variables that should be expanded when using `add_library` in the plugin `CMakeLists.txt`.

### `docs`

The plugin `docs` folder should describe all of the benchmarks created by the plugin.

### `LICENSE.txt`

The license that the plugin code is release under (if any).

### README.md

The readme should describe the objective of the plugin, the contributors of the plugin, and how to cite the plugin.

### `src`

All the source files for the benchmarks should be in `src`.
The organization within `src` is up to the developer.

## Adding the plugin to Scope (Required)

First, this plugin should be added to scope as a submodule:

    cd scope
    git submodule add git@github.com:rai-project/example_scope.git

Then, the submodule URL should be changed to be cloned in the same way as scope was.
Th `url` field in `scope/.gitmodules` for the submodule should be modified to be a relative path.
For example, if the submodule is hosted under `rai-project/example_scope.git`, it would look like:

```
[submodule "example_scope"]
	path = example_scope
	url = ../example_scope.git
```

If the submodule is hosted under `your-account/new_scope.git`, it would look like:

```
[submodule "new_scope"]
	path = new_scope
	url = ../../your-account/new_scope.git
```

This means that if scope is cloned with https, your submodule will be too.
If scope is cloned with ssh, your submodule will be too.

Then, the [scope CMakeLists.txt](https://github.com/rai-project/scope/blob/master/CMakeLists.txt) should be modified to load this plugin.

An option to enable your scope should be added near the beginning of the CMakeLists.txt file:

```cmake
option(ENABLE_EXAMPLE "Include Example|Scope (github.com/rai-project/example_scope)" ON)
```

A snippet of code to add your scope to the build should be added further down, after the main scope `add_executable(...)`.

```cmake
if (ENABLE_EXAMPLE)
  message(STATUS "Enabling Example|Scope")
  add_subdirectory(${TOP_DIR}/example_scope)
  target_link_libraries(bench example_scope)
endif(ENABLE_EXAMPLE)
```

## Scope Utilities (Optional)

The plugin may (should) make use of utilities provided by Scope in scope.
Those utilities can be included with `#include scope/utils/...`

## Scope Initialization (Optional)

Scope allows plugins to register initialization callbacks in scope/src/init.hpp (if desired).
These callbacks will be invoked with no guaranteed ordering before `main()` is executed.

Callbacks are `void (*fn)(int argc, char **argv)` functions that will be passed the command line flags that Scope is executed with.
Callbacks can be registered with the INIT() macro:

```cpp
// plugin/src/init.cpp
#include "scope/init/init.hpp

void plugin_init(int argc, char **argv) {
    (void) argc;
    (void) argv;
}

INIT(pugin_init);
```

## Citation

Please cite the following when referring to this work:
