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