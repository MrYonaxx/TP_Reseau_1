# CMakeList.txt : projet CMake pour NetworkLib, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (NetworkLib "NetworkLib.cpp" "NetworkLib.h" "Terminal.cpp" "Terminal.h" "Connection.cpp" "Connection.h" "ConnectionTCP.cpp" "ConnectionTCP.h" "ConnectionUDP.cpp" "ConnectionUDP.h")

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
