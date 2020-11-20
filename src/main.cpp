#include <SDL.h>
#include <examples/ExampleGame.h>

int main(int argc, char* args[]) { //sdl requires this type of main so it's compatible with multiple platforms
    ExampleGame exampleGame{};
    exampleGame.init();
    exampleGame.initGLData();
    exampleGame.update();

    return 0;
}