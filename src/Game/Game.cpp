#include <windows.h>
#include <cctype>
#include <iostream>
#include <format>

#include "Game.hpp"
#include "Board.hpp"
#include "../Input/Input.hpp"
#include "../Renderer/Renderer.hpp"

Game::Game()
: currentScore(0), bestScore(500)
{
    Renderer::loadFont();
    Renderer::loadTextures();
    this->run();
    // this->bestScore = save.load();
}

Game::~Game()
{
}

void Game::update()
{
}

void Game::run()
{
    Board board = Board();
    while(true)
    {   
        Sleep(100);
        Renderer::clear();
        if(!board.gridIsFull())
        {
            currentScore += board.checkMove();
        }
        Renderer::drawText("Score           Meilleur", "default", 20, std::tuple<int,int>(300,400));
        Renderer::drawText(std::to_string(currentScore) + "                 " + std::to_string(bestScore) + "\n", "default", 20, std::tuple<int, int>(300, 400));
        board.printBoard();
        if (Input::getPressed("Escape"))
        {
            std::cout << "Closing Programm" << std::endl;
            break;
        }

        if (Input::getPressed("r"))
        {
            board.initializeBoard();
        }
    }
}

