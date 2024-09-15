#ifndef GAME_H
#define GAME_H
#include <string>
class Game
{
private:
    int currentScore;
    int bestScore;
    std::string texturesPath;
    std::string fontsPath;
    void checkScore();
public:
    static float deltaTime;
    Game();
    ~Game();
    void run();
};

#endif