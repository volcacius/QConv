#Define src files
set(QCONV_TEST_SRC test.c)
set(QCONV_TEST_SRC ${QCONV_TEST_SRC} signed_types/qconv_test_utils_int32.c)
set(QCONV_TEST_SRC ${QCONV_TEST_SRC} signed_types/qconv_test_int32.c)

set(QCONV_TEST_SRC ${QCONV_TEST_SRC} unsigned_types/qconv_test_uint16.c)
set(QCONV_TEST_SRC ${QCONV_TEST_SRC} unsigned_types/qconv_test_utils_uint16.c)
set(QCONV_TEST_SRC ${QCONV_TEST_SRC} unsigned_types/qconv_test_uint16_mod_m_13.c)
set(QCONV_TEST_SRC ${QCONV_TEST_SRC} unsigned_types/qconv_test_uint16_mod_f_3.c)
set(QCONV_TEST_SRC ${QCONV_TEST_SRC} gnmnt.c)

#Define output executable
add_executable(qconv_test ${QCONV_TEST_SRC})

#Link against the the dependencies
target_link_libraries(qconv_test
         qconv_lib)

#Add the header dir
target_include_directories(qconv_test PRIVATE
         ${PROJECT_SOURCE_DIR}/include/src
         ${PROJECT_SOURCE_DIR}/include/src/unsigned_types
         ${PROJECT_SOURCE_DIR}/include/src/signed_types
         ${PROJECT_SOURCE_DIR}/include/test
         ${PROJECT_SOURCE_DIR}/include/test/signed_types
         ${PROJECT_SOURCE_DIR}/include/test/unsigned_types)