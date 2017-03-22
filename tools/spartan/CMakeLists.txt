include_directories(../../include)
add_executable(spartan program.c)
target_link_libraries(spartan libspartan)
