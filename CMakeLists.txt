cmake_minimum_required(VERSION 3.6)
project(QConv)

#Set C language requirements
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

#Set build type
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_VERBOSE_MAKEFILE ON)

#Add subdir for compiling the library on which the executable depends on
add_subdirectory(src)
#Add subdir for compiling the tests
add_subdirectory(test)

#Define executable src files
set(QCONV_EXE_SRC main.c include/src/qconv_int64.h)

#Define output executable
add_executable(qconv_exe ${QCONV_EXE_SRC})

#Link against the library dependencies
target_link_libraries(qconv_exe
        PRIVATE qconv_lib)