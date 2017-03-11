cmake_minimum_required(VERSION 3.6)

#Set C language requirements
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

#Set build type
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_VERBOSE_MAKEFILE ON)

#Define src files
set(QCONV_LIB_SRC qconv_int16.c)
set(QCONV_LIB_SRC ${QCONV_LIB_SRC} qconv_int32.c)
set(QCONV_LIB_SRC ${QCONV_LIB_SRC} qconv_int32_ntt_constants.c)

#Define output static library
add_library(qconv_lib STATIC ${QCONV_LIB_SRC})

#Add the header dir
target_include_directories(qconv_lib
        PRIVATE ${PROJECT_SOURCE_DIR}/include/src) #PROJECT_SOURCE_DIR is CMake defined and corresponds to the dir where
                                              #the CMakeLists.txt containing project(QConv) is located