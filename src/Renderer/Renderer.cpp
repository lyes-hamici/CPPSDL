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
void Renderer::draw(int (&board)[4][4]){}

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
    TTF_Init();
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
    SDL_SetRenderDrawColor(Renderer::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Renderer::renderer);
}
void Renderer::loadTextures()
{
    SDL_Surface *surf;

    for (int i = 2; i < 65537; i *= 2)
    {
        std::string filePath = "Images/" + std::to_string(i) + ".png";
        surf = IMG_Load(filePath.c_str());
        Renderer::images[std::to_string(i)] = SDL_CreateTextureFromSurface(Renderer::renderer, surf);
        SDL_FreeSurface(surf);
    }

    surf = IMG_Load("Images/0.png");
    Renderer::images["0"] = SDL_CreateTextureFromSurface(Renderer::renderer, surf);
    surf = IMG_Load("Images/Background.png");
    Renderer::images["Background"] = SDL_CreateTextureFromSurface(Renderer::renderer, surf);
    surf = IMG_Load("Images/Text.png");
    Renderer::images["Text"] = SDL_CreateTextureFromSurface(Renderer::renderer, surf);
    surf = IMG_Load("Images/Grid_background.png");
    Renderer::images["Grid_background"] = SDL_CreateTextureFromSurface(Renderer::renderer, surf);
   
    SDL_FreeSurface(surf);
}

void Renderer::loadFont()
{

}

void Renderer::draw()
{                        // Clear the screen
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
void Renderer::draw(int (&board)[4][4])
{
    SDL_RenderCopy(Renderer::renderer, Renderer::images["Background"], NULL, NULL);
    
    int tileSize = 80;                              
    int spacing = 8;                                
    int gridWidth = (4 * tileSize) + (3 * spacing);  
    int gridHeight = (4 * tileSize) + (3 * spacing); 

    int startX = (600 - gridWidth) / 2;
    int startY = (700 - gridHeight) / 2;

    SDL_Rect gridBackgroundRect = {startX - 40, startY - 40, gridWidth + 80, gridHeight + 80};
    SDL_SetTextureAlphaMod(Renderer::images["Grid_background"], 200);
    SDL_RenderCopy(Renderer::renderer, Renderer::images["Grid_background"], NULL, &gridBackgroundRect);
    
    SDL_Rect textRect = {startX - 40, 20, gridWidth + 80, 100};
    SDL_Rect scoreRect = {startX - 40, gridHeight + startY + 60, gridWidth + 80, 100};
    SDL_RenderCopy(Renderer::renderer, Renderer::images["Text"], NULL, &textRect);
    SDL_RenderCopy(Renderer::renderer, Renderer::images["Text"], NULL, &scoreRect);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            int value = board[row][col]; 

            SDL_Rect tilesRect = {
                startX + col * (tileSize + spacing),
                startY + row * (tileSize + spacing), 
                tileSize,                            
                tileSize                             
            };

            std::string textureKey = std::to_string(value);
            if (Renderer::images.find(textureKey) != Renderer::images.end())
            {
                SDL_RenderCopy(Renderer::renderer, Renderer::images[textureKey], NULL, &tilesRect);
            }
        }
    }

    SDL_RenderPresent(Renderer::renderer);
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
std::map<std::string, sf::Texture> Renderer::images;
    void Renderer::initialize(){
        window.create(sf::VideoMode(600,700),"SFML 2048");
    }

    // Détruire la fenêtre (si nécessaire)
    void Renderer::destroy() {
        if (window.isOpen()) {
            window.close();
        }
    }

    // Effacer la fenêtre
    void Renderer::clear() {
        window.clear();
    }

    // Charger une texture depuis un fichier
    void Renderer::loadTextures() {
        int tileValues[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};  // Les valeurs de tuiles possibles
        for (int value : tileValues) {
            sf::Texture texture;
            std::string filename = "../textures/" + std::to_string(value) + ".png";  // Chemin du fichier
            if (texture.loadFromFile(filename)) {
                Renderer::images[std::to_string(value)] = texture;
            } else {
                std::cerr << "Erreur: Impossible de charger la texture pour la tuile " << value << " depuis " << filename << std::endl;
            }
        }
    }

    // Charger une police depuis un fichier
        void Renderer::loadFont() {
        // sf::Font font;
        // if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {  // Adjust path to Arial font
        //     fonts["arial"] = font;
        // }
        // Load other fonts if needed
    }

    // Dessiner une texture spécifique
    void Renderer::draw() {
    }
    void Renderer::drawRow(void *row, int size){}

    // Dessiner un texte
    void Renderer::drawText(std::string text, std::string fontName, int fontSize, std::tuple<int, int> pos) {
        // sf::Text sfText;
        // sfText.setFont(fonts[fontName]);
        // sfText.setString(text);
        // sfText.setCharacterSize(fontSize);
        // sfText.setPosition(std::get<0>(pos), std::get<1>(pos));
        // window.draw(sfText);
    }

    // Dessiner une grille de jeu (board)
   // Draw the game board (4x4 grid for the 2048 game)
    void Renderer::draw(int (&board)[4][4]) {
        float tileSize = 100.0f;  // Size of each tile
        for (size_t row = 0; row < 4; ++row) {
            for (size_t col = 0; col < 4; ++col) {
                int value = board[row][col];

                // Dessiner la texture associée à la valeur de la tuile si elle existe
                if (value > 0) {
                    sf::Sprite sprite;
                    sprite.setTexture(images[std::to_string(value)]);
                    sprite.setPosition(col * tileSize, row * tileSize);
                    window.draw(sprite);
                } else {
                    // Si la texture n'existe pas, dessiner un rectangle basique avec une couleur
                    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                    tile.setPosition(col * tileSize, row * tileSize);
                    tile.setFillColor(sf::Color(200, 200, 200));  // Couleur pour une tuile vide ou sans texture
                    window.draw(tile);

                    // Si la valeur est > 0 mais pas de texture associée, afficher la valeur en texte
                    
                }
            }
        }
        window.display();
    }




    // Obtenir la résolution de la fenêtre
    std::tuple<int, int> Renderer::getResolution() {
        sf::Vector2u size = window.getSize();
        return std::tuple<int, int>(size.x, size.y);
    }


// Définir les membres statiques

// std::map<std::string, sf::Font> Renderer::fonts;
#endif