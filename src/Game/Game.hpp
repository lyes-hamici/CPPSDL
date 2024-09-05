#ifndef GAME_H
#define GAME_H

class Game
{
private:
    int currentScore = 0;
    int bestScore;
public:
    Game(/* args */);
    ~Game();

    void update();
    void initialize();
    void run();
};

#endif