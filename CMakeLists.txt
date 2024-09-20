cmake_minimum_required(VERSION 3.26)
project(HtpConnection)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_DEBUG_POSTFIX d)
include_directories(include
                    src)
file(GLOB SRCS "include/*" "src/*")
add_executable(HttpConnection ${SRCS})
set_target_properties(HttpConnection PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

target_link_libraries(HttpConnection fmt::fmt)
set_target_properties( HttpConnection PROPERTIES LIBRARY_OUTPUT_DIRECTORY "Release" )
set_target_properties( HttpConnection PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "Debug"  )
set_target_properties( HttpConnection PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "Release"  )
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
