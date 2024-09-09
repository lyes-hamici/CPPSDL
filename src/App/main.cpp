#include "../Game/Game.hpp"
// #include "../Input/Input.cpp"
#include "../Input/InputSDL.hpp"
#include "../Renderer/Renderer.hpp"

int main(int argc, char *argv[])
{
    // Input::WindowsConsole::initialize();
    // Renderer::WindowsConsole::initialize();
    Renderer::initialize();
    InputSDL::initialize();
    Game game = Game();
    Renderer::destroy();
    return 0;
}

