//
// Created by eduard.parvu on 10/13/2020.
//

#ifndef SDL2_OPENGL_VULKAN_ENGINE_EXAMPLEGAME_H
#define SDL2_OPENGL_VULKAN_ENGINE_EXAMPLEGAME_H

#include<SDL.h>


class ExampleGame {
private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
    SDL_Event event{};
    bool quit = false;
    bool vSyncAvailable = true;
    unsigned int vao{};

    void render();
    void close();

public:
    ExampleGame(const ExampleGame& other) = delete; // copy not allowed through the copy constructor
    ExampleGame(ExampleGame&& other) = delete; // move not allowed through the move constructor
    ExampleGame& operator=(const ExampleGame& other) = delete; // copy not allowed through the copy operator
    ExampleGame& operator=(ExampleGame && other) = delete; // move not allowed through the move operator

    ExampleGame();

    bool init();
    bool initGLData();
    void handleInput();
    void update();

};


#endif //SDL2_OPENGL_VULKAN_ENGINE_EXAMPLEGAME_H
