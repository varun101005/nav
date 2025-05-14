cmake_minimum_required(VERSION 3.10)
project(TransportNavigation)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)

# Include header files
include_directories(include)

# Add executable and source files
add_executable(transport_navigation
    src/main.cpp
    src/Graph.cpp
    src/Dijkstra.cpp
    src/FloydWarshall.cpp
)