#include "../Game/Game.hpp"
#include "../Input/Input.hpp"
#include "../Renderer/Renderer.hpp"
int main(int argc, char *argv[])
{
    Input::initialize();
    Renderer::initialize();
    Game game = Game();
    Renderer::destroy();
    return 0;
}

