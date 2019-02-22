cmake_minimum_required(VERSION 3.13)

project(graphics_editor C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall")

find_package(SDL2 REQUIRED)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(/usr/include/readline ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(graphics_editor src/main.c src/parsing.c src/parsing.h src/traitement_image.c src/traitement_image.h src/includes.h src/traitement_fenetre.c src/traitement_fenetre.h)
target_link_libraries(graphics_editor readline ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})



