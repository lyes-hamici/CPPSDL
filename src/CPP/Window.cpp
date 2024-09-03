#include <SDL2/SDL.h>
#include <iostream>
#include "Window.hpp"


void inputPoll()
{
    
}

Window::Window(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL: " << SDL_GetError() << std::endl;
    }

    // Créer une fenêtre SDL
    SDL_Window* window = SDL_CreateWindow("Ma Fenêtre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,400, 400,SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Erreur lors de la création de la fenêtre: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Erreur lors de la création du renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // Couleur initiale de fond
    int r = 10, g = 10, b = 10;

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } 
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_r:
                        r = 255; g = 0; b = 0;   // Rouge
                        break;
                    case SDLK_g:
                        r = 0; g = 255; b = 0;   // Vert
                        break;
                    case SDLK_b:
                        r = 0; g = 0; b = 255;   // Bleu
                        break;
                    case SDLK_w:
                        r = 255; g = 255; b = 255; // Blanc
                        break;
                    case SDLK_ESCAPE:
                        quit = true;             // Quitter avec la touche Echap
                        break;
                    default:
                        break;
                }
            }
        }

        // Changer la couleur de fond
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);

        // Effacer l'écran
        SDL_RenderClear(renderer);

        // Mettre à jour l'écran
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};


Window::~Window(){
    //dtor
}