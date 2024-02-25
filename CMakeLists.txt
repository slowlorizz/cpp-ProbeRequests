
# Set CMake version
cmake_minimum_required(VERSION 3.9)

# Set project name
project(prq)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set build output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find libtins package
find_package(tins REQUIRED)

# Add executable target
add_executable(prq main.cpp)

# Link libtins library

target_link_libraries(prq tins)
