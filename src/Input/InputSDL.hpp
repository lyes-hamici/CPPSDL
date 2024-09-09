#ifndef INPUTSDL_H
#define INPUTSDL_H

#include <map>
#include <string>
#include <SDL_keyboard.h>
#include <SDL.h>

class InputSDL
{
private:
    /* data */
public:
    static void initialize();
    static bool getPressed(std::string name);
    static bool getPressed(char character);
    static std::map<std::string, SDL_KeyCode> keys;
    static bool wasPressed;
    static SDL_KeyCode keyPressed;
};



#endif