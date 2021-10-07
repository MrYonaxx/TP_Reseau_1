# CMakeList.txt : CMake project for Server, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Server "Server.cpp" "Server.h")

target_link_libraries(Server PUBLIC ${PROJECT_NAME})