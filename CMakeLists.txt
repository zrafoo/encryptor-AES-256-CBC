cmake_minimum_required(VERSION 3.10)
project(FileEncryptor C)

set(CMAKE_C_STANDARD 99)

find_package(OpenSSL REQUIRED)

add_executable(MyEncryptor main.c encryption.c decryption.c keygen.c)
target_link_libraries(MyEncryptor OpenSSL::SSL OpenSSL::Crypto)
