#ifndef INPUT_H
#define INPUT_H

// #define USE_WINDOWSCONSOLE // For coding purposes - ERASE THIS
// #define USE_SDL // For coding purposes - ERASE THIS
// #define USE_SFML // For coding purposes - ERASE THIS

#include <map>
#include <string>
#include <cctype>
#include <iostream> // Just for debuggin - ERASE THIS

#ifdef USE_WINDOWSCONSOLE
#include <windows.h>
#endif

#ifdef USE_SDL
#include "../LibSDL/SDL.h"
#endif

#ifdef USE_SFML
#include <SFML/Window/Keyboard.hpp>
#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::milliseconds
#endif

class Input
{
private:
    static bool wasPressed;
    static std::string keyPressed;

public:
    static void initialize();
    static bool getPressed(std::string name);
    static bool getPressed(char character);

#ifdef USE_WINDOWSCONSOLE
    static std::map<std::string, int> keys;
#endif

#ifdef USE_SDL
    static std::map<std::string, SDL_KeyCode> keys;
#endif

#ifdef USE_SFML
    static std::map<std::string, sf::Keyboard::Key> keys;
#endif
};

#endif