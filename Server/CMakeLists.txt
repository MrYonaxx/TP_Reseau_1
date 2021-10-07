# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#

cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
include_directories(../NetworkLib/NetworkLib)
link_libraries(Lib/NetworkLib)

include_directories(../NetworkLib/NetworkLib)

add_library(NetworkLib STATIC IMPORTED)
set_property(TARGET NetworkLib PROPERTY IMPORTED_LOCATION ${CMAKE_HOME_DIRECTORY}/Lib/NetworkLibs.lib)
set_property(TARGET NetworkLib PROPERTY IMPORTED_IMPLIB ${CMAKE_HOME_DIRECTORY}/Lib/NetworkLibs.lib)
add_executable(ServerExe Server/Server.cpp)
target_link_libraries(ServerExe PRIVATE NetworkLib)

option(BUILD_EXAMPLES "build examples" ON)
option(BUILD_TESTS "build tests" ON)

project ("Server")

# Include sub-projects.
add_subdirectory ("Server")
