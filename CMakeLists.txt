# versao do cmake
cmake_minimum_required(VERSION 3.10)

# definição da aplicacao
project(DRAW_PIXELS_SDL)

# definir o compilador
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER gcc)

# define o arquivo executavel
add_executable(DRAW_PIXELS_SDL main.c)


# CONFIGURAÇÃO DAS BIBLIOTECAS

### Define o PATH para as bibliotecas SDL
set(SDL2_DIR "./SDL2/lib/cmake/SDL2")
set(SDL2_ttf_DIR "./SDL2/lib/cmake/SDL2_ttf")
set(SDL2_image_DIR "./SDL2/lib/cmake/SDL2_image")

### Procurar as bibliotecas necessárias
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

### Linka as bibliotecas à aplicação
target_link_libraries(DRAW_PIXELS_SDL SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image)






