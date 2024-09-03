#include "GameBoard.hpp"
#include <random>
#include <cstring>

// Init & Destroy functions
GameBoard::GameBoard()
{
    initializeBoard();
}

GameBoard::~GameBoard()
{
}

void GameBoard::initializeBoard()
{
    resetBoard();
    generateRandomTile();
    generateRandomTile();
}

void GameBoard::resetBoard()
{
    // for (int i = 0; i < boardSize; i++)
    // {
    //     for (int j = 0; j < boardSize; j++)
    //     {
    //         board[i][j] = 0;
    //     }
    // }

    std::memset(board, 0, 16 * sizeof(int));
}

//--------------Game Logic--------------//
// Verifications
bool GameBoard::verifyFreeTile(int i, int j)
{
    return board[i][j] == 0;
}
// Generations
void GameBoard::generateRandomTile()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);
    std::uniform_int_distribution<> tilePercent(0, 9);

    int i, j;
    do
    {
        i = dist(gen);
        j = dist(gen);
    } while (board[i][j] != 0);

    board[i][j] = tilePercent(gen) < 9 ? 2 : 4;
}

// Moves
void GameBoard::move(char *str)
{
}

void GameBoard::moveUp()
{
}

void GameBoard::moveDown()
{
}

void GameBoard::moveLeft()
{
}

void GameBoard::moveRight()
{
}
