# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
include_directories(../NetworkLib/NetworkLib)

add_library(NetworkLib STATIC IMPORTED)
set_property(TARGET NetworkLib PROPERTY IMPORTED_LOCATION ${CMAKE_HOME_DIRECTORY}/Lib/NetworkLibs.lib)
set_property(TARGET NetworkLib PROPERTY IMPORTED_IMPLIB ${CMAKE_HOME_DIRECTORY}/Lib/NetworkLibs.lib)
add_executable(ClientExe Client/Client.cpp)
target_link_libraries(ClientExe PRIVATE NetworkLib)

option(BUILD_EXAMPLES "build examples" ON)
option(BUILD_TESTS "build tests" ON)

project ("Client")

# Include sub-projects.
add_subdirectory ("Client")