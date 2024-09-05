#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <string>

class Input
{
private:
    /* data */
public:
    static void initialize();
    static bool getPressed(std::string name);
    static bool getPressed(char character);
    static std::map<std::string, int> keys;
};

#endif