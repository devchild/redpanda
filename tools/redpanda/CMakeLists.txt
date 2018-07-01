include_directories(../../include)
add_executable(redpanda program.c)
target_link_libraries(redpanda libredpanda)
