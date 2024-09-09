#ifndef RENDERER_H
#define RENDERER_H

#include <tuple>
#include <string>

#ifdef USE_WINDOWSCONSOLE
#include <iostream>
#include <iomanip>
#endif

#ifdef USE_SDL
#include <map>
#include <SDL.h>
#endif

#ifdef USE_SFML
#include <map>
#include <SFML/Graphics.hpp>
#endif

class Renderer
{
private:
public:
    static void initialize();
    static void destroy();
    static void clear();
    static void loadTextures();
    static void loadFont();
    static void draw();
    static void drawRow(void *row, int size);
    static void drawText(std::string text, std::string fontName, int fontSize, std::tuple<int, int> pos);
    static std::tuple<int, int> getResolution();

#ifdef USE_SDL
    // static std::map<std::string, SDL_Images> images;
#endif

#ifdef USE_SFML
    static sf::RenderWindow window;
// std::map<std::string, sf::Texture> Input::images;
// std::map<std::string, sf::Font> Input::fonts;
#endif
};

#endif