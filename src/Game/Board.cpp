#include "Board.hpp"
#include <random>
#include <cstring>

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
    int sum = 0;
    char direction;
    int fordward[4] = {0, 1, 2, 3};
    int backward[4] = {3, 2, 1, 0};
    bool isPositive = (direction == 'L' || direction == 'U');
    bool isHorizontal = (direction == 'L' || direction == 'R');
    int step = isPositive ? 1 : -1;

    for (int i = 0; i < 4; i++)
    {
        int target = isPositive ? 0 : 3;
        for (auto &j : isPositive ? fordward : backward)
        {
            int x = isHorizontal? i : j;
            int y = isHorizontal? j : i;

            if (board[x][y] != 0)
            {
                if (y != target)
                {
                    board[x][target] = board[x][y];
                    board[x][y] = 0;
                }
                target++;
            }
        }

        for (auto &j : isPositive ? fordward : backward)
        {
            int x = isHorizontal ? i : j;
            int y = isHorizontal ? j : i;
            
            if (board[x][y] != 0 && board[x][y] == board[x][y + step])
            {
                sum += board[x][y] *2;
                board[x][y] *= 2;
                board[x][y + step] = 0;
            }
        }

        int target = isPositive ? 0 : 3;
        for (auto &j : isPositive ? fordward : backward)
        {
            int x = isHorizontal ? i : j;
            int y = isHorizontal ? j : i;

            if (board[x][y] != 0)
            {
                if (y != target)
                {
                    board[x][target] = board[x][y];
                    board[x][y] = 0;
                }
                target++;
            }
        }
    }
    return sum;
}