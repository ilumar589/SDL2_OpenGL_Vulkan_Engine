#include <SDL.h>
#include <examples/ExampleGame.h>
#include <examples/Examples.h>
#include "Shader.h"

int main(int argc, char* args[]) { //sdl requires this type of main so it's compatible with multiple platforms
    GameContext *game_context = GameContext_create();
    game_context->vao = Examples::triangleVertexArrayBuffer();
    Shader shader{"resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl"};
    shader.use();
    GameContext_update(game_context);
    return 0;
}