FIND_PACKAGE(Threads REQUIRED) #for Cimg
FIND_PACKAGE(X11) # for Cimg
include_directories(${X11_INCLUDE_DIRS}) #for Cimg


SET(all_srcs main.cpp)
ADD_EXECUTABLE(fit ${all_srcs})
TARGET_LINK_LIBRARIES(fit libdij)
TARGET_LINK_LIBRARIES(fit ${CMAKE_THREAD_LIBS_INIT} ${X11_LIBRARIES}) #cimg
