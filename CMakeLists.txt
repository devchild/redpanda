cmake_minimum_required (VERSION 2.8)
project (snowball C)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# Add sub-directories
add_subdirectory(tools)
add_subdirectory(lib)
