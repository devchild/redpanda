include_directories(../../include)
add_executable(snowball program.c)
target_link_libraries(snowball libsnowball)
