#include "../Game/Game.hpp"
#include "../Input/Input.cpp"

int main(int argc, char *argv[])
{
    // Input::WindowsConsole::initialize();
    // Renderer::WindowsConsole::initialize();
    Input::initialize();
    Game game = Game();
    return 0;
}