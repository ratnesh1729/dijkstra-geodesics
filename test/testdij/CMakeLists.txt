include_directories("${PROJECT_SOURCE_DIR}")

file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testdij ${SRCS})

TARGET_LINK_LIBRARIES(testdij
    libdij
    libgtest
    libgmock
)

add_test(NAME testdij
         COMMAND testdij)
