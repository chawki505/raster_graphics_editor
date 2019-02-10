cmake_minimum_required(VERSION 3.13)

project(raster_graphics_editor C)
set(CMAKE_C_STANDARD 11)
find_package(SDL2 REQUIRED)

add_executable(raster_graphics_editor main.c)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(raster_graphics_editor ${SDL2_LIBRARIES})



