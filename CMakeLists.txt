cmake_minimum_required(VERSION 3.9)

project(prq)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(prq main.cpp)
target_link_libraries(prq tins)