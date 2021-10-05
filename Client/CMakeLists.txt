# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
include_directories(../NetworkLib/NetworkLib)
link_libraries(Lib/NetworkLib)

option(BUILD_EXAMPLES "build examples" ON)
option(BUILD_TESTS "build tests" ON)

project ("Client")

# Include sub-projects.
add_subdirectory ("Client")