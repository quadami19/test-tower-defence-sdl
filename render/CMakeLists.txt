cmake_minimum_required (VERSION 3.5)

set(LIBRARY_NAME render)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_library(render ${SOURCE_FILES})

target_link_libraries(render ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_include_directories(${LIBRARY_NAME} PRIVATE include)

