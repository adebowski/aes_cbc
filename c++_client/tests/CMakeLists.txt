cmake_minimum_required(VERSION 3.12)
project(secure_config)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_definitions(-DUNIT_TESTS)

add_subdirectory(googletest)
include(GoogleTest)

set(SRC_ROOT "${CMAKE_SOURCE_DIR}")
set(LIBRARY_SRC
    ${SRC_ROOT}/Parser.cpp
    ${SRC_ROOT}/AESUtils.cpp
)

set(LIBRARY_INCLUDES
    ${SRC_ROOT}/
)

add_library(libraries_to_test ${LIBRARY_SRC})
target_include_directories(libraries_to_test PUBLIC ${LIBRARY_INCLUDES})
target_link_libraries(libraries_to_test PUBLIC gmock_main)

set(TESTFILES
    ParserTest.cpp
)

add_executable(decryptor_tests ${TESTFILES})
target_link_libraries(decryptor_tests PUBLIC gtest_main gmock_main)
target_link_libraries(decryptor_tests PRIVATE libraries_to_test)
target_compile_options(decryptor_tests PRIVATE -Werror -Wall)

target_include_directories(decryptor_tests PUBLIC ${OPENSSL_INCLUDE_DIR})

find_package(OpenSSL REQUIRED)

if(OPENSSL_FOUND)
    target_link_libraries(decryptor_tests PUBLIC OpenSSL::SSL OpenSSL::Crypto)
    target_include_directories(decryptor_tests PUBLIC ${OPENSSL_INCLUDE_DIR})

    # Add the static lib for linking
    message(STATUS "Found OpenSSL ${OPENSSL_VERSION}")

else()
    message(STATUS "OpenSSL Not Found")
endif()

# Add the static lib for linking
gtest_discover_tests(decryptor_tests)
