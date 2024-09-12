#include <windows.h>
#include <cctype>
#include <iostream>
#include <format>
#include <string>

#include "Game.hpp"
#include "Board.hpp"
#include "File.hpp"
#include "../Input/Input.hpp"
#include "../Renderer/Renderer.hpp"

Game::Game()
    : currentScore(0)
{
    Renderer::loadFont();
    Renderer::loadTextures();
    bestScore = File::loadScore("Score.save");
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
    while (true)
    {
        Sleep(16);
        Renderer::clear();
        if (!board.gridIsFull())
        {
            currentScore += board.checkMove();
        }
        Renderer::drawText("Score           Meilleur", "Arial", 20, std::tuple<int, int>{300, 400});
        Renderer::drawText(std::to_string(currentScore) + "                 " + std::to_string(bestScore) + "\n", "Arial", 20, std::tuple<int, int>{300, 400});
        board.printBoard();
        Renderer::draw(board.board);
        Renderer::drawText("Press r to reset the game", "Arial", 20, std::tuple<int, int>{300, 400});
        if (Input::getPressed("Escape"))
        {
            std::cout << "Closing Programm" << std::endl;
            break;
        }
        if (Input::getPressed("r"))
        {
            checkScore();
            currentScore = 0;
            board.initializeBoard();
        }
        if (board.gridIsFull())
        {
            Renderer::drawText("Game ended", "Arial", 20, std::tuple<int, int>(300, 400));
            checkScore();
        }
        Renderer::display();
    }
}

void Game::checkScore()
{
    if (currentScore > bestScore)
    {
        File::saveScore(currentScore, "Score.save");
        bestScore = currentScore;
    }
}
