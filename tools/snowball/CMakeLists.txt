include_directories(../../include)
add_executable(snowball program.c fmemopen.c)
target_link_libraries(snowball libsnowball)
include_directories("../../include")
