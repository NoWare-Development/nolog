cmake_minimum_required(VERSION 3.3)

set(LIBRARY_NAME_STATIC nologstatic)
set(LIBRARY_NAME_SHARED nologshared)

set(TEST_NAME test)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb")

set(SOURCE
  "${CMAKE_SOURCE_DIR}/src/nolog.c"
  )

add_library(nologobj OBJECT ${SOURCE})
target_include_directories(nologobj PUBLIC "${CMAKE_SOURCE_DIR}/include")
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
