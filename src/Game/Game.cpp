#include <windows.h>
#include <cctype>
#include <iostream>

#include "Game.hpp"
#include "Board.hpp"
#include "../Input/Input.hpp"

Game::Game()
: currentScore(0), bestScore(500)
{
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
        if(!board.gridIsFull())
        {
            currentScore += board.checkMove();
        }
        board.checkMove();
        board.printBoard(board.board);
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

