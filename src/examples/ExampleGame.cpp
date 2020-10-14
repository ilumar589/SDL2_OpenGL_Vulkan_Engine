//
// Created by eduard.parvu on 10/13/2020.
//

#include "ExampleGame.h"
#include <glad/glad.h>
#include <iostream>
#include <Shader.h>

bool ExampleGame::init() {
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()
                  << std::endl;

        return false;
    }

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window) {
        std::cout << "Window could not be created! SDL_Error "
                  << SDL_GetError()
                  << std::endl;

        return false;
    }

    // Use OpenGL 3.3 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    glContext = SDL_GL_CreateContext(window);

    if (!glContext) {
        std::cout << "OpenGL context could not be created! SDL Error: "
                  << SDL_GetError()
                  << std::endl;
        return false;
    }

    SDL_GL_MakeCurrent(window, glContext);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    if (SDL_GL_SetSwapInterval(1) < 0) {
        vSyncAvailable = false;
        std::cout << "Warning: Unable to set Vsync! SDL Error: "
                  << SDL_GetError()
                  << std::endl;
    }

    return true;
}

bool ExampleGame::initGLData() {

    Shader shader{"resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl"};

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top

    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    // as we only have a single shader, we could also just activate our shader once beforehand if we want to
    shader.use();

    vao = VAO;

    return true;
}

void ExampleGame::handleInput() {
    while (SDL_PollEvent(&event)) {
        //User requests quit
        if( event.type == SDL_QUIT ){
            quit = true;
        }
    }
}

void ExampleGame::update() {
    while (!quit) {
        handleInput();
        render();
    }

    close();
}

void ExampleGame::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    // render the triangle
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // PRESENT BACKBUFFER:
    SDL_GL_SwapWindow(window);
}

void ExampleGame::close() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

ExampleGame::ExampleGame() = default;
