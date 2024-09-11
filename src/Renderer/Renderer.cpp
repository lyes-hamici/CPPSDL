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
std::map<std::string, SDL_Texture*> Renderer::images;
SDL_Window* Renderer::window;
SDL_Renderer* Renderer::renderer;
void Renderer::initialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    // TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_AVIF);
    Renderer::window = SDL_CreateWindow("Ma Fenêtre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 700, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cerr << "Erreur lors de la création de la fenêtre: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    Renderer::renderer = SDL_CreateRenderer(Renderer::window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer::renderer == nullptr)
    {
        std::cerr << "Erreur lors de la création du renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(Renderer::window);
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
    std::string path = "Images/";
    SDL_Surface *surf;
    for (int i = 2; i < 65537; i *= 2)
    {
        std::string filePath = path + std::to_string(i) + ".png";
        surf = IMG_Load(filePath.c_str());
        Renderer::images[std::to_string(i)] = SDL_CreateTextureFromSurface(Renderer::renderer, surf);
        SDL_FreeSurface(surf);
    }
    surf = IMG_Load("Images/0.png");
    Renderer::images["0"] = SDL_CreateTextureFromSurface(Renderer::renderer, surf);
    SDL_FreeSurface(surf);
}

void Renderer::loadFont()
{

}

void Renderer::draw()
{
    SDL_SetRenderDrawColor(Renderer::renderer, 255, 0, 0, 255); // Set background color
    SDL_RenderClear(Renderer::renderer);                        // Clear the screen

    int xPosition = 0;     // Initial x position
    int yPosition = 50;    // Fixed y position (line)
    int imageWidth = 50;  // Width of each image
    int imageHeight = 50; // Height of each image
    int spacing = 10;      // Space between images

    for (int i = 2; i < 65537; i *= 2)
    {
        SDL_Rect dstRect = {xPosition, yPosition, imageWidth, imageHeight}; // Set position and size
        SDL_RenderCopy(Renderer::renderer, Renderer::images[std::to_string(i)], NULL, &dstRect);

        xPosition += imageWidth + spacing; // Move x position for next image
    }

    SDL_RenderPresent(Renderer::renderer); // Display rendered content
}
void Renderer::draw(int (&grid)[4][4])
{
    SDL_SetRenderDrawColor(Renderer::renderer, 255, 0, 0, 255); // Set background color
    SDL_RenderClear(Renderer::renderer);                        // Clear the screen

    int tileSize = 100;                              // Size of each tile (width and height)
    int spacing = 10;                                // Spacing between the tiles
    int gridWidth = (4 * tileSize) + (3 * spacing);  // Total width of the grid
    int gridHeight = (4 * tileSize) + (3 * spacing); // Total height of the grid

    // Centering the grid on a 600x700 screen
    int startX = (600 - gridWidth) / 2;
    int startY = (700 - gridHeight) / 2;

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            int value = grid[row][col]; // Get the value from the grid

            SDL_Rect dstRect = {
                startX + col * (tileSize + spacing), // x position
                startY + row * (tileSize + spacing), // y position
                tileSize,                            // width
                tileSize                             // height
            };

            std::string textureKey = std::to_string(value); // Use the grid value to get the corresponding texture
            if (Renderer::images.find(textureKey) != Renderer::images.end())
            {
                SDL_RenderCopy(Renderer::renderer, Renderer::images[textureKey], NULL, &dstRect);
            }
        }
    }

    SDL_RenderPresent(Renderer::renderer); // Display rendered content
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