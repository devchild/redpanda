find_package(GLib)
find_package(GObject)

include_directories(
    ${GLib_INCLUDE_DIRS}
    ${GObject_INCLUDE_DIRS}
    ../../include
)

add_executable(redpanda program.c)
target_link_libraries(redpanda libredpanda ${GLib_LIBRARY} ${GObject_LIBRARY})
