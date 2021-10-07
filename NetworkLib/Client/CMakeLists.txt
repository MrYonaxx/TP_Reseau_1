# CMakeList.txt : CMake project for Client, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Client "Client.cpp")

target_link_libraries(Client PUBLIC ${PROJECT_NAME})