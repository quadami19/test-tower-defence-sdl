cmake_minimum_required (VERSION 3.16)

set(LIBRARY_NAME map)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_library(${LIBRARY_NAME} ${SOURCE_FILES})

target_include_directories(${LIBRARY_NAME} PRIVATE include)

target_link_libraries(${LIBRARY_NAME} object)
