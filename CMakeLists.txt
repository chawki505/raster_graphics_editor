cmake_minimum_required(VERSION 3.13)

project(graphics_editor C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(/usr/include/readline)

add_executable(graphics_editor src/main.c src/parsing.c src/parsing.h src/traitement_image.c src/traitement_image.h src/includes.h)

target_link_libraries(graphics_editor ${SDL2_LIBRARIES} readline)



