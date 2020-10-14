cmake_minimum_required(VERSION 3.17)
project(SDL2_OpenGL_Vulkan_Engine)

set(CMAKE_CXX_STANDARD 17)

# add sdl cmake files to the cmake module path where for find_package function to work
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2")

# copy sdl dependencies
file(COPY ${CMAKE_SOURCE_DIR}/dependencies/SDL2 DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/dependencies/SDL2/msvc/libraries/x64/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR})
# copy glad dependencies
file(COPY ${CMAKE_SOURCE_DIR}/dependencies/glad DESTINATION ${CMAKE_BINARY_DIR})
# copy resources
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

# override variables to point to the SDL2 dependency distributed with the executable
set(SDL2_INCLUDE_DIR ${CMAKE_BINARY_DIR}/SDL2/msvc/include)
set(SDL2_LIBRARY  ${CMAKE_BINARY_DIR}/SDL2/msvc/libraries/x64/SDL2.lib)
set(SDL2MAIN_LIBRARY  ${CMAKE_BINARY_DIR}/SDL2/msvc/libraries/x64/SDL2main.lib)

find_package(SDL2 REQUIRED)
#find_package(SDL2_net REQUIRED)
#find_package(SDL2_mixer REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_gfx REQUIRED)
#find_package(SDL2_ttf REQUIRED)

find_package(OpenGL REQUIRED)

set(SOURCE_FILES
        src/glad.c
        src/main.cpp
        src/examples/ExampleGame.cpp src/examples/ExampleGame.h src/Shader.cpp src/Shader.h)

include_directories(dependencies/glad/include)
include_directories(src)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL::GL)
target_link_libraries(${CMAKE_PROJECT_NAME} SDL2::Main)
#target_link_libraries(${CMAKE_PROJECT_NAME} SDL2::Main SDL2::Net SDL2::Mixer SDL2::Image SDL2::TTF SDL2::GFX) all the SDL2 dependencies are linked here as an example

