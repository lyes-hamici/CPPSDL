#include <iostream>
#include <random>
#include <cstring>

#include "Board.hpp"
// #include "../Input/Input.hpp"
#include "../Input/InputSDL.hpp"
#include "../Renderer/Renderer.hpp"

// Init & Destroy functions
Board::Board()
{
    initializeBoard();
}

Board::~Board()
{
}

void Board::initializeBoard()
{
    resetBoard();
    generateRandomTile();
    generateRandomTile();
}

void Board::resetBoard()
{
    std::memset(board, 0, 16 * sizeof(int));
}

//--------------Board Logic--------------//
// Verifications
bool Board::verifyFreeTile(int i, int j)
{
    return board[i][j] == 0;
}
// Generations
void Board::generateRandomTile()
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
int Board::checkMove()
{
    char direction = 0;
    if (InputSDL::getPressed("Left"))
    {
        direction = 'L';
    }
    if (InputSDL::getPressed("Right"))
    {
        direction = 'R';
    }
    if (InputSDL::getPressed("Up"))
    {
        direction = 'U';
    }
    if (InputSDL::getPressed("Down"))
    {
        direction = 'D';
    }
    if (direction == 0)
    {
        return 0;
    }
    int sum = 0;
    int fordward[4] = {0, 1, 2, 3};
    int backward[4] = {3, 2, 1, 0};
    bool isPositive = (direction == 'L' || direction == 'U');
    bool isHorizontal = (direction == 'L' || direction == 'R');
    int step = isPositive ? 1 : -1;
    bool moved = false;

    for (auto &i : fordward)
    {
        int target = isPositive ? 0 : 3;
        for (auto &j : isPositive ? fordward : backward)
        {
            int x = isHorizontal ? i : j;
            int y = isHorizontal ? j : i;

            if (board[x][y] != 0)
            {
                if (j != target)
                {
                    if (isHorizontal)
                    {
                        board[x][target] = board[x][y];
                    }
                    else
                    {
                        board[target][y] = board[x][y];
                    }
                    board[x][y] = 0;
                    moved = true;
                }
                target += step;
            }
        }

        for (auto &j : isPositive ? fordward : backward)
        {
            int x = isHorizontal ? i : j;
            int y = isHorizontal ? j : i;

            if (isHorizontal)
            {
                if ((y + step >= 0 && y + step < 4) && board[x][y] != 0 && board[x][y] == board[x][y + step])
                {
                    sum += board[x][y] * 2;
                    board[x][y] *= 2;
                    board[x][y + step] = 0;
                    moved = true;
                }
            }
            else
            {
                if ((x + step >= 0 && x + step < 4) && board[x][y] != 0 && board[x][y] == board[x + step][y])
                {
                    sum += board[x][y] * 2;
                    board[x][y] *= 2;
                    board[x + step][y] = 0;
                    moved = true;
                }
            }
        }

        target = isPositive ? 0 : 3;
        for (auto &j : isPositive ? fordward : backward)
        {
            int x = isHorizontal ? i : j;
            int y = isHorizontal ? j : i;

            if (board[x][y] != 0)
            {
                if (j != target)
                {
                    if (isHorizontal)
                    {
                        board[x][target] = board[x][y];
                    }
                    else
                    {
                        board[target][y] = board[x][y];
                    }
                    board[x][y] = 0;
                    moved = true;
                }
                target += step;
            }
        }
    }
    if (moved){generateRandomTile();}
    return sum;
}

void Board::printBoard()
{
    for (auto &i : board)
    {
        Renderer::drawRow(i, 4);
    }
}

bool Board::gridIsFull()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (board[i][j] == 0)
            {
                return false; // Grid is not full, there are empty tiles
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (j < 3 && board[i][j] == board[i][j + 1])
            {
                return false;
            }

            if (i < 3 && board[i][j] == board[i + 1][j])
            {
                return false;
            }
        }
    }
    return true;
}

// int main()
// {
//     Input::initialize();
//     Board board = Board();
//     while (true)
//     {
//         Sleep(100);
//         board.checkMove();
//         board.printBoard(board.board);
//         // system("cls");
//         if (Input::getPressed("Escape"))
//         {
//             std::cout << "Closing Programm" << std::endl;
//             return 0;
//         }

//         if (Input::getPressed("r"))
//         {
//             board.initializeBoard();
//         }
//     }
//     return 0;
// }