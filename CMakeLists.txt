cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

function(scope_status)
  message(STATUS "[Example|Scope] ${ARGV}")
endfunction()

# Look for sugar.cmake files in the plugin src directory
sugar_include("src")

# The plugin is a static library that Scope will be linked with
add_library(example_scope OBJECT ${example_SOURCES} ${example_CUDA_SOURCES} )
target_include_directories(example_scope PRIVATE 
    ${SRC_DIR}
    ${THIRDPARTY_DIR}
    ${TOP_DIR}/include
    ${CUDA_INCLUDE_DIRS}
    "src"
)

git_get_head_revision(EXAMPLE_GIT_REFSPEC EXAMPLE_GIT_HASH)
git_local_changes(EXAMPLE_GIT_LOCAL_CHANGES)
scope_status(GIT_REFSPEC=${EXAMPLE_GIT_REFSPEC})
scope_status(GIT_HASH=${EXAMPLE_GIT_HASH})
scope_status(GIT_LOCAL_CHANGES=${EXAMPLE_GIT_LOCAL_CHANGES})

target_compile_features(example_scope PUBLIC cxx_std_11)
set_property(TARGET example_scope PROPERTY CUDA_STANDARD 11)
target_link_libraries(example_scope PRIVATE benchmark::benchmark)
