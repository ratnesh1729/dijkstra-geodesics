SET(OpenCV_DIR "/home/ratnesh/Downloads/opencv-3.2.0/build/")
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(Threads REQUIRED) #for Cimg
FIND_PACKAGE(X11) # for Cimg
include_directories(${X11_INCLUDE_DIRS}) #for Cimg


SET(all_srcs main.cpp)
ADD_EXECUTABLE(fit ${all_srcs})
TARGET_LINK_LIBRARIES(fit ${OpenCV_LIBS} libdij)
TARGET_LINK_LIBRARIES(fit ${CMAKE_THREAD_LIBS_INIT} ${X11_LIBRARIES}) #cimg
