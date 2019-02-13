option(ENABLE_EXAMPLE "Include Example|Scope (github.com/c3sr/example_scope)" ON)
if(NOT ENABLE_EXAMPLE)
  return()
endif()

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Example|Scope LANGUAGES CXX VERSION 1.0.1)

# Look for sugar.cmake files in the plugin src directory
sugar_include(src)

# The scope is an object library that SCOPE will be linked with
scope_add_library(example_scope OBJECT ${example_SOURCES})

# The scope should have some include directories from SCOPE
target_include_scope_directories(example_scope)

# The scope requires linking against SCOPE's libraries
target_link_scope_libraries(example_scope)

# Example|Scope may have other includes or other properties too, like any other CMake project
target_include_directories(example_scope PRIVATE 
    ${PROJECT_BINARY_DIR}/src
    src
)
target_compile_features(example_scope PUBLIC cxx_std_11)
set_property(TARGET example_scope PROPERTY CUDA_STANDARD 11)

# Get the git version to fill the config.hpp file
git_get_head_revision(GIT_REFSPEC GIT_HASH)
git_local_changes(GIT_LOCAL_CHANGES)
scope_status(GIT_REFSPEC=${GIT_REFSPEC})
scope_status(GIT_HASH=${GIT_HASH})
scope_status(GIT_LOCAL_CHANGES=${GIT_LOCAL_CHANGES})
scope_status("${PROJECT_SOURCE_DIR}/src/config.hpp.in -> ${PROJECT_BINARY_DIR}/src/config.hpp")
configure_file (
    "${PROJECT_SOURCE_DIR}/src/config.hpp.in"
    "${PROJECT_BINARY_DIR}/src/config.hpp"
)
