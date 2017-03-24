#Define src files
set(QCONV_LIB_SRC unsigned_types/qconv_uint16.c)
set(QCONV_LIB_SRC ${QCONV_LIB_SRC} unsigned_types/qconv_uint8.c)
set(QCONV_LIB_SRC ${QCONV_LIB_SRC} unsigned_types/qconv_uint8_mod_m_8.c)
set(QCONV_LIB_SRC ${QCONV_LIB_SRC} unsigned_types/qconv_uint16_mod_f_8.c)
set(QCONV_LIB_SRC ${QCONV_LIB_SRC} unsigned_types/qconv_uint16_mod_f_8_constants.c)
set(QCONV_LIB_SRC ${QCONV_LIB_SRC} unsigned_types/qconv_uint16_mod_m_13.c)
set(QCONV_LIB_SRC ${QCONV_LIB_SRC} unsigned_types/qconv_uint32.c)

set(QCONV_LIB_SRC ${QCONV_LIB_SRC} signed_types/qconv_int32.c)
set(QCONV_LIB_SRC ${QCONV_LIB_SRC} signed_types/qconv_int32_mod_12289.c)
set(QCONV_LIB_SRC ${QCONV_LIB_SRC} signed_types/qconv_int32_mod_12289_constants.c)

#Define output static library
add_library(qconv_lib STATIC ${QCONV_LIB_SRC})

#Add the header dirs
#PROJECT_SOURCE_DIR is CMake defined and corresponds to the dir where the CMakeLists.txt containing project(QConv) is located
target_include_directories(qconv_lib
        PRIVATE ${PROJECT_SOURCE_DIR}/include/src/unsigned_types
                ${PROJECT_SOURCE_DIR}/include/src/signed_types
                ${PROJECT_SOURCE_DIR}/include/src)
