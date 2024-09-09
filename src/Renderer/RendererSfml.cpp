#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class RendererSFML {
private:
    sf::RenderWindow window;
    std::map<std::string, sf::Texture> images;
    std::map<std::string, sf::Font> fonts;

public:
    // Constructor that initializes the window and the maps
    void initialize() {
        window.create(sf::VideoMode(800 , 600), "2048 SFML");
    }

    // Load a texture from a file
    void loadTextures(const std::string &name, const std::string &filename) {
        sf::Texture texture;
        if (texture.loadFromFile(filename)) {
            images[name] = texture;
        }
    }

    // Load a font from a file
    void loadFont(const std::string &name, const std::string &filename) {
        sf::Font font;
        if (font.loadFromFile(filename)) {
            fonts[name] = font;
        }
    }

    // Draw a texture on the window
    void draw(const std::string &name, float x, float y) {
        sf::Sprite sprite;
        sprite.setTexture(images[name]);
        sprite.setPosition(x, y);
        window.draw(sprite);
    }

    // Draw text on the window
    void drawText(const std::string &fontName, const std::string &text, float x, float y, unsigned int size = 30) {
        sf::Text sfText;
        sfText.setFont(fonts[fontName]);
        sfText.setString(text);
        sfText.setCharacterSize(size);
        sfText.setPosition(x, y);
        window.draw(sfText);
    }

    // Clear the window
    void clear() {
        window.clear();
    }

    // Display the window
    void display() {
        window.display();
    }


    // Close the window
    void close() {
        window.close();
    }

    // Clean up textures and fonts
    void quitTextures() {
        images.clear();
        fonts.clear();
    }
};