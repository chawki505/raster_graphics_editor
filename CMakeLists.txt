cmake_minimum_required(VERSION 3.13)

project(graphics_editor C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall")

find_package(SDL2 REQUIRED)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(/usr/include/readline ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(graphics_editor src/main.c src/parsing/parsing.c src/parsing/parsing.h src/gestions/traitement_image/traitement_image.c src/gestions/traitement_image/traitement_image.h src/includes.h src/gestions/traitement_fenetre/traitement_fenetre.c src/gestions/traitement_fenetre/traitement_fenetre.h src/gestions/my_struct_images/my_struct_images.c src/gestions/my_struct_images/my_struct_images.h)
target_link_libraries(graphics_editor readline ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})



