#ifndef BOARD_H
#define BOARD_H

class Board
{
private:

int boardSize = 4;

//Internal functions - Manage board and test tiles
void generateRandomTile();
bool verifyFreeTile(int i, int j);

public:
//Init & Dest
    Board();
    ~Board();
    void initialize();
    void reset();
    bool gridIsFull();
//Logic for moves
    int checkMove(); // An idea find a better way
    // The  board - is an array of 4 x 4 elements - stored in the stack
    int tiles[4][4];
    void render();
};


#endif