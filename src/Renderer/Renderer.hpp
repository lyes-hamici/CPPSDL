#ifndef RENDERER_H
#define RENDERER_H

#include <tuple>
#include <string>
#include <iostream>

// #define USE_SFML

#ifdef USE_WINDOWSCONSOLE
#include <iomanip>
#endif

#ifdef USE_SDL
#include <map>
#include <SDL2/SDL.h>
#include <SDL_image.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
#endif

#ifdef USE_SFML
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <tuple>
#include <vector>
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
    static void draw(int (&board)[4][4]);
    static void drawRow(void *row, int size);
    static void drawText(std::string text, std::string fontName, int fontSize, std::tuple<int, int> pos);
    static std::tuple<int, int> getResolution();

#ifdef USE_SDL
    // static std::map<std::string, SDL_Images> images;
#endif

#ifdef USE_SFML
    static sf::RenderWindow window;
    static std::map<std::string, sf::Texture> images;
// std::map<std::string, sf::Font> Input::fonts;
#endif
};

#endif