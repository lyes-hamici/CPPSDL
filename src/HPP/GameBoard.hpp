#ifndef GAMEBOARD_H
#define GAMEBOARD_H

class GameBoard
{
private:

int boardSize = 4;

//Internal functions - Manage board and test tiles
void generateRandomTile();
bool verifyFreeTile(int i, int j);

public:
//Init & Dest
    GameBoard();
    ~GameBoard();
    void initializeBoard();
    void resetBoard();

//Logic for moves
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void move(char *str); // An idea find a better way

// The game board - is an array of 4 x 4 elements - stored in hte stack
    int board[4][4];
};


#endif