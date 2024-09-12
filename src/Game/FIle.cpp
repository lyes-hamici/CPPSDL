#include "File.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

void File::saveScore(int score, std::string filePath)
{
    std::ofstream fout;
    fout.open(filePath);

    fout << std::to_string(score);
    fout.close();
}

int File::loadScore(std::string filePath)
{
    std::fstream fio = std::fstream(filePath, std::ios::in);
    std::string line;

    if (!fio) {return 0;}
    auto fileLenght = (int)std::filesystem::file_size(filePath);
    if (fileLenght < 1) {return 0;}

    auto inputStream = std::ostringstream() << fio.rdbuf();

    return std::stoi(inputStream.str());
}