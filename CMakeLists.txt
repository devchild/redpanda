cmake_minimum_required (VERSION 2.8)
project (spartan C)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# Add sub-directories
add_subdirectory(tools)
add_subdirectory(lib)

