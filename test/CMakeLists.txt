#Define src files
set(QCONV_TEST_SRC test.c)
set(QCONV_TEST_SRC ${QCONV_TEST_SRC} qconv_test_int32.c)
set(QCONV_TEST_SRC ${QCONV_TEST_SRC} qconv_test_utils_int32.c)

#Define output executable
add_executable(qconv_test ${QCONV_TEST_SRC})

#Link against the the dependencies
target_link_libraries(qconv_test
        PRIVATE qconv_lib)

#Add the header dir
target_include_directories(qconv_test
        PRIVATE ${PROJECT_SOURCE_DIR}/include/src
        PRIVATE ${PROJECT_SOURCE_DIR}/include/test) #PROJECT_SOURCE_DIR is CMake defined and corresponds to the dir where
                                                    #the CMakeLists.txt containing project(QConv) is located