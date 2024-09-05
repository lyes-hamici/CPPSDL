#include "Game.hpp"
#include "Board.hpp"

Game::Game()
: bestScore(500)
{
    this->run();
    // this->bestScore = save.load();
}

Game::~Game()
{
}

void Game::run()
{
    Board board = Board();
    while(true)
    {
        if(!board.gridIsFull())
        {
            currentScore += board.checkMove();
        }
    }
}

