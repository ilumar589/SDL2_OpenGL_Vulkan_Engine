#include <SDL.h>
#include <examples/ExampleGame.h>
#include <examples/Examples.h>

int main(int argc, char* args[]) { //sdl requires this type of main so it's compatible with multiple platforms
    GameContext *game_context = GameContext_create();
    Examples::GLuint2 vao_and_texture = Examples::loadTexture();
    Shader shader{"resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl"};

    game_context->vao = vao_and_texture.value1;
    game_context->textureHandle = vao_and_texture.value2;
    game_context->shader = shader;

    GameContext_update(game_context);

    return 0;
}