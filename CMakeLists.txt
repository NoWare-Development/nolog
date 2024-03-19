cmake_minimum_required(VERSION 3.5)

#
### LIBRARY
#
set(LIBRARY_NAME nolog)
project(${LIBRARY_NAME})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

if(UNIX AND NOT APPLE)
  message(STATUS "Compiling for Linux...")
elseif(WIN32)
  message(STATUS "Compiling for Windows...")
else()
  message(SEND_ERROR "Unknown platform. Your OS is not supported.")
endif()

set(SOURCE
  "${CMAKE_SOURCE_DIR}/src/nolog.c"
  "${CMAKE_SOURCE_DIR}/src/log_thread_linux.c"
  "${CMAKE_SOURCE_DIR}/src/log_thread_win32.c"
  "${CMAKE_SOURCE_DIR}/src/log_queue.c"
  )

add_library(${LIBRARY_NAME} SHARED ${SOURCE})
set_property(TARGET ${LIBRARY_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)
target_include_directories(${LIBRARY_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

#
### TEST APPLICATION
#
set(TEST_NAME test)
project(${TEST_NAME})

set(TEST_SRC
  "${CMAKE_SOURCE_DIR}/test/test.c"
  )

add_executable(${TEST_NAME} ${TEST_SRC})

target_include_directories(${TEST_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${TEST_NAME} ${LIBRARY_NAME})
