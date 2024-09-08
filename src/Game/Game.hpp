#ifndef GAME_H
#define GAME_H

class Game
{
private:
    int currentScore;
    int bestScore;

    void checkScore();
public:
    Game();
    ~Game();

    void update();
    void run();
};

#endif