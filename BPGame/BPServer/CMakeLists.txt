cmake_minimum_required(VERSION 3.17)
project(BPServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(BPServer main.cpp BPServer.cpp BPServer.h BacktrackingAlgorithm.cpp BacktrackingAlgorithm.h AStarAlgorithm.cpp AStarAlgorithm.h MapConstants.h ../../LinkedList/List.h)