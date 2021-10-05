# CMakeList.txt : CMake project for Server, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Server "Server.cpp" "Server.h" "NetworkLib/NetworkLib.cpp" "NetworkLib/NetworkLib.h" "NetworkLib/Terminal.cpp" "NetworkLib/Terminal.h" "NetworkLib/Connection.cpp" "NetworkLib/Connection.h" "NetworkLib/ConnectionTCP.cpp" "NetworkLib/ConnectionTCP.h" "NetworkLib/ConnectionUDP.cpp" "NetworkLib/ConnectionUDP.h")

# TODO: Add tests and install targets if needed.
