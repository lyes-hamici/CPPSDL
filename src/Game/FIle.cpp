#include "File.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

void File::saveScore(int score, std::string filePath)
{
    if (score < 0)
        return;

    std::ofstream fout;
    fout.open(filePath);
    fout << std::to_string(score);
    fout.close();
}

int File::loadScore(std::string filePath)
{
    std::fstream fio = std::fstream(filePath, std::ios::in);
    std::string line;

    if (!fio)
        return 0; 
    auto fileLength = (int)std::filesystem::file_size(filePath);
    if (fileLength < 1)
        return 0; 

    fio >> line;
    return std::stoi(line);
}
