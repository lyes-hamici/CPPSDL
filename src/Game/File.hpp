#ifndef FILE_H
#define FILE_H

#include <string>

class File
{ 
public:
    static int saveScore(int score, std::string filePath);
    static int loadScore(std::string filePath);
};


#endif