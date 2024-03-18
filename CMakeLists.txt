cmake_minimum_required(VERSION 3.3)

set(LIBRARY_NAME_STATIC nologstatic)
set(LIBRARY_NAME_SHARED nologshared)

set(TEST_NAME test)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb")

if (UNIX AND NOT APPLE)
  set (PLATFORM "-DPLATFORM_LINUX")
elseif(WIN32)
  set (PLATFORM "-DPLATFORM_WIN32")
else()
  set (PLATFORM "-DPLATFORM_UNKNOWN")
endif()

set(SOURCE
  "${CMAKE_SOURCE_DIR}/src/nolog.c"
  "${CMAKE_SOURCE_DIR}/src/log_thread_linux.c"
  "${CMAKE_SOURCE_DIR}/src/log_thread_win32.c"
  "${CMAKE_SOURCE_DIR}/src/log_queue.c"
  )

add_library(nologobj OBJECT ${SOURCE})
target_include_directories(nologobj PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_compile_definitions(nologobj PUBLIC ${PLATFORM})
set_property(TARGET nologobj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(${LIBRARY_NAME_SHARED} SHARED $<TARGET_OBJECTS:nologobj>)
add_library(${LIBRARY_NAME_STATIC} STATIC $<TARGET_OBJECTS:nologobj>)

project(${TEST_NAME})

set(TEST_SRC
  "${CMAKE_SOURCE_DIR}/test/test.c"
  )

add_executable(${TEST_NAME} ${TEST_SRC})

target_include_directories(${TEST_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${TEST_NAME} ${LIBRARY_NAME_STATIC})
