set(libdij_SRCS
    dijkstra.h
    dijkstra.cpp
)

# Declare the library
add_library(libdij STATIC
    ${libdij_SRCS}
)

# Specify here the include directories exported
# by this library
#target_include_directories(libfoo PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}
#)
