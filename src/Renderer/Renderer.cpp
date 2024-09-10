#include "Renderer.hpp"

#ifdef USE_WINDOWSCONSOLE
void Renderer::initialize(){}

void Renderer::destroy(){}

void Renderer::clear(){
    system("cls");
}

void Renderer::loadTextures(){}

void Renderer::loadFont(){}

void Renderer::draw()
{
}

void Renderer::drawRow(void *row, int size)
{
    int *intRow = (int *)row;

    int width = 5;

    for (int j = 0; j < size; j++)
    {
        std::cout << std::setw(width) << intRow[j] << " ";
    }

    std::cout << "\n" << std::endl;
}

void Renderer::drawText(std::string text, std::string fontName, int fontSize, std::tuple<int, int> pos)
{
    std::cout << text << std::endl;

}

std::tuple<int, int> Renderer::getResolution()
{
    return std::tuple<int,int>();
}

#endif

#ifdef USE_SDL
// std::map<std::string, SDL_Images> Renderer::textures;
void Renderer::initialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    // TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_AVIF);
    SDL_Window *window = SDL_CreateWindow("Ma Fenêtre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cerr << "Erreur lors de la création de la fenêtre: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cerr << "Erreur lors de la création du renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

void Renderer::destroy()
{

}

void Renderer::clear()
{

}
void Renderer::loadTextures()
{

}
void Renderer::loadFont()
{

}

void Renderer::draw()
{

}

void Renderer::drawRow(void *row, int size)
{

}

void Renderer::drawText(std::string text, std::string fontName, int fontSize, std::tuple<int, int> pos)
{

}

std::tuple<int, int> Renderer::getResolution()
{
    return std::tuple<int, int>();
}

#endif

#ifdef USE_SFML
sf::RenderWindow Renderer::window;
// std::map<std::string, sf::Texture> Renderer::images;
// std::map<std::string, sf::Font> Renderer::fonts;
void Renderer::initialize()
{
    window.create(sf::VideoMode(800, 600), "2048 SFML");
}

void Renderer::destroy()
{
}

void Renderer::clear()
{
}
void Renderer::loadTextures()
{
}
void Renderer::loadFont()
{
}

void Renderer::draw()
{
}

void Renderer::drawRow(void *row, int size)
{
}

void Renderer::drawText(std::string text, std::string fontName, int fontSize, std::tuple<int, int> pos)
{
}

std::tuple<int, int> Renderer::getResolution()
{
    return std::tuple<int, int>();
}
#endif