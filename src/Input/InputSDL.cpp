#include "InputSDL.hpp"


#include <windows.h>
#include <cctype>
#include <iostream>

std::map<std::string, SDL_KeyCode> InputSDL::keys;

void InputSDL::initialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
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
    InputSDL::keys["Left"] = SDLK_LEFT;
    InputSDL::keys["Right"] = SDLK_RIGHT;
    InputSDL::keys["Up"] = SDLK_UP;
    InputSDL::keys["Down"] = SDLK_DOWN;
    InputSDL::keys["Escape"] = SDLK_ESCAPE;
    InputSDL::keys["Return"] = SDLK_RETURN;
    InputSDL::keys["r"] = SDLK_r;
}

bool InputSDL::getPressed(char character)
{
    // if (!std::isalpha(character))
    // {
    //     return false;
    // }
    // character = std::toupper(character);
    // // DO something here
    return false;
}
bool InputSDL::getPressed(std::string name)
{
    if (name.empty())
    {
        return false;
    }

    // if (name.length() == 1)
    // {
    //     return getPressed(name[0]);
    // }
    if (InputSDL::keys.contains(name))
    {
        SDL_PumpEvents();
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        SDL_Scancode scancode = SDL_GetScancodeFromKey(InputSDL::keys[name]);
        if (state[scancode])
        {
            // std::cout << "Key : " << name << std::endl;
            return true;
        }
        else
        {
            return false;
        }
        // return state[scancode];

        // if (state[scancode] & SDL_KEYDOWN)
        // {
        //     std::cout << "Key : " << name << "Pressed" << std::endl;
        //     return true;
        // }
        // if (state[scancode] & SDL_KEYUP)
        // {
        //     return false;
        // }

        // return SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromKey(InputSDL::keys[name])];
        
        // SDL_Event event;
        // while (SDL_PollEvent(&event))
        // {
        //     if (event.type == SDL_KEYDOWN)
        //     {
        //         if (event.key.keysym.sym == keys[name])
        //         {
        //             std::cout << "Key : " << name << "Pressed" << std::endl;
        //             return true;
        //         }
        //         return false;
        //     }
        //     return false;
        // }
    }

        return false;
}
