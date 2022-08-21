cmake_minimum_required(VERSION 3.0.0)
project(Decryptor VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(tests)

add_executable(Decryptor main.cpp TCPClient.cpp AESUtils.cpp Parser.cpp)

find_package(OpenSSL REQUIRED)

if(OPENSSL_FOUND)
    # Add the include directories for compiling
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENSSL_INCLUDE_DIR})

    # Add the static lib for linking
    target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)
    message(STATUS "Found OpenSSL ${OPENSSL_VERSION}")

else()
    message(STATUS "OpenSSL Not Found")
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include(CPack)
