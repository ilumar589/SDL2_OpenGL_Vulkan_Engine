//
// Created by eduard.parvu on 10/13/2020.
//

#ifndef SDL2_OPENGL_VULKAN_ENGINE_EXAMPLEGAME_H
#define SDL2_OPENGL_VULKAN_ENGINE_EXAMPLEGAME_H

#include <glad/glad.h>
#include<SDL.h>
#include <Shader.h>


struct GameContext {
    SDL_Window *window = nullptr;
    SDL_GLContext gl_context = nullptr;
    SDL_Event  event{};
    bool quit = false;
    bool v_sync_available = true;
    GLuint vao{};
    GLuint textureHandle{};
    Shader shader;
};

GameContext* GameContext_create();
void GameContext_destroy(GameContext *);
void GameContext_handle_input(GameContext *);
void GameContext_update(GameContext *);
void GameContext_render(GameContext *);

#endif //SDL2_OPENGL_VULKAN_ENGINE_EXAMPLEGAME_H
