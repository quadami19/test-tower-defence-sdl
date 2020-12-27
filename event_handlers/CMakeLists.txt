cmake_minimum_required (VERSION 3.5)

set(LIBRARY_NAME event_handlers)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_library(${LIBRARY_NAME} ${SOURCE_FILES})

target_include_directories(${LIBRARY_NAME} PRIVATE include)

