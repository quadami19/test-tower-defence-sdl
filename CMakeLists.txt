cmake_minimum_required (VERSION 3.5)

set(PROJECT_NAME tower-defence-sdl)
list(APPEND EXTRA_LIBS object event_handlers)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${EXTRA_LIBS})

add_subdirectory(object)
add_subdirectory(event_handlers)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/media/pics" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/media)
