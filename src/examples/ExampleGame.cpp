//
// Created by eduard.parvu on 10/13/2020.
//

#include "ExampleGame.h"
#include <iostream>
#include <memory>


GameContext * GameContext_create() {
    auto *game_context = static_cast<GameContext*>(calloc(1, sizeof(GameContext)));

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()
                  << std::endl;
    }

    game_context->window = SDL_CreateWindow("SDL Tutorial",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            800,
                                            600,
                                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!game_context->window) {
        printf("Window could not be created! SDL_Error %s", SDL_GetError());
    }

    // Use OpenGL 3.3 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    game_context->gl_context = SDL_GL_CreateContext(game_context->window);

    if (!game_context->gl_context) {
        SDL_SetError("OpenGL context could not be created! SDL Error: %s", SDL_GetError());
    }

    SDL_GL_MakeCurrent(game_context->window, game_context->gl_context);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("OpenGL context could not be created! SDL Error: %s", SDL_GetError());
    }

    if (SDL_GL_SetSwapInterval(1) < 0) {
        game_context->v_sync_available = false;
        printf("Warning: Unable to set Vsync! SDL Error: %s", SDL_GetError());
    }


    return game_context;
}

void GameContext_destroy(GameContext *game_context) {
    SDL_DestroyWindow(game_context->window);
    free(game_context);
    SDL_Quit();
}

void GameContext_handle_input(GameContext *game_context) {
    while (SDL_PollEvent(&game_context->event)) {
        //User requests quit
        if( game_context->event.type == SDL_QUIT ){
            game_context->quit = true;
        }
    }
}

void GameContext_update(GameContext *game_context) {
    while (!game_context->quit) {
        GameContext_handle_input(game_context);
        GameContext_render(game_context);
    }
    GameContext_destroy(game_context);
}

void GameContext_render(GameContext *game_context) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    glBindTexture(GL_TEXTURE_2D, game_context->textureHandle);
    game_context->shader.use();
    glBindVertexArray(game_context->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    // PRESENT BACKBUFFER:
    SDL_GL_SwapWindow(game_context->window);
}
