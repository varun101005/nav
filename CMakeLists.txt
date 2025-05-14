cmake_minimum_required(VERSION 3.10)
project(TransportNavigation)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)

# Include header files
include_directories(include)

# Add cpp-httplib
include(FetchContent)
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.12.0
)
FetchContent_MakeAvailable(httplib)

# Add executable and source files
add_executable(transport_navigation
    src/main.cpp
    src/Graph.cpp
    src/Dijkstra.cpp
    src/FloydWarshall.cpp
)

# Link libraries
target_link_libraries(transport_navigation PRIVATE httplib)