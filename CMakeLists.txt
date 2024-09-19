cmake_minimum_required(VERSION 3.26)
project(HtpConnection)
set(CMAKE_CXX_STANDARD 17)
include_directories(include
                    src)
file(GLOB SRCS "include/*" "src/*")
add_executable(HttpConnection ${SRCS})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)