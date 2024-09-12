#include <iostream>
#include <random>
#include <cstring>

#include "Board.hpp"
#include "../Input/Input.hpp"
#include "../Renderer/Renderer.hpp"

Board::Board(){initialize();}
Board::~Board(){}

void Board::initialize()
{
    reset();
    generateRandomTile();
    generateRandomTile();
}

void Board::reset()
{
    std::memset(tiles, 0, sizeof(tiles));
}

//--------------Board Logic--------------//
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
    } while (tiles[i][j] != 0);

    tiles[i][j] = tilePercent(gen) < 9 ? 2 : 4;
}

// Moves
int Board::checkMove()
{
    char direction = 0;
    if (Input::getPressed("Left"))
    {
        direction = 'L';
    }
    else if (Input::getPressed("Right"))
    {
        direction = 'R';
    }
    else if (Input::getPressed("Up"))
    {
        direction = 'U';
    }
    else if (Input::getPressed("Down"))
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

            if (tiles[x][y] != 0)
            {
                if (j != target)
                {
                    if (isHorizontal)
                    {
                        tiles[x][target] = tiles[x][y];
                    }
                    else
                    {
                        tiles[target][y] = tiles[x][y];
                    }
                    tiles[x][y] = 0;
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
                if ((y + step >= 0 && y + step < 4) && tiles[x][y] != 0 && tiles[x][y] == tiles[x][y + step])
                {
                    sum += tiles[x][y] * 2;
                    tiles[x][y] *= 2;
                    tiles[x][y + step] = 0;
                    moved = true;
                }
            }
            else
            {
                if ((x + step >= 0 && x + step < 4) && tiles[x][y] != 0 && tiles[x][y] == tiles[x + step][y])
                {
                    sum += tiles[x][y] * 2;
                    tiles[x][y] *= 2;
                    tiles[x + step][y] = 0;
                    moved = true;
                }
            }
        }

        target = isPositive ? 0 : 3;
        for (auto &j : isPositive ? fordward : backward)
        {
            int x = isHorizontal ? i : j;
            int y = isHorizontal ? j : i;

            if (tiles[x][y] != 0)
            {
                if (j != target)
                {
                    if (isHorizontal)
                    {
                        tiles[x][target] = tiles[x][y];
                    }
                    else
                    {
                        tiles[target][y] = tiles[x][y];
                    }
                    tiles[x][y] = 0;
                    moved = true;
                }
                target += step;
            }
        }
    }
    if (moved){generateRandomTile();}
    return sum;
}

void Board::render()
{
    for (auto &i : tiles)
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
            auto isEmpty = tiles[i][j] == 0;
            auto canMergeHorizontal = j < 3 && tiles[i][j] == tiles[i][j + 1];
            auto canMergeVertical = i < 3 && tiles[i][j] == tiles[i + 1][j];
            if(isEmpty || canMergeHorizontal || canMergeVertical){
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