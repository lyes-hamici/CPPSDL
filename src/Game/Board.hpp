#ifndef BOARD_H
#define BOARD_H
#include "Tile.hpp"
class Board
{
private:

//Internal functions - Manage board and test tiles
void generateRandomTile();
bool verifyFreeTile(int i, int j);

public:
//Init & Dest
    Board();
    ~Board();
    int tileSize;
    void initialize();
    void reset();
    bool gridIsFull();
//Logic for moves
    int checkMove(); // An idea find a better way
    bool checkAnimations();
    // The  board - is an array of 4 x 4 elements - stored in the stack
    Tile cache[4*4];
    Tile* tiles[4][4];
    void render();
};


#endif