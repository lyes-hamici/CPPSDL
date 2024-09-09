#include <iostream>
#include <iomanip>

#include "Renderer.hpp"

void Renderer::initialize(){}

void Renderer::destroy(){}

void Renderer::clear(){
    system("cls");
}

void Renderer::loadTextures(){}

void Renderer::loadFont(){}

void Renderer::draw()
{
}

void Renderer::drawRow(void *row, int size)
{
    int *test = (int *)row;

    // Assuming a width of 5 characters for each number, you can adjust this as needed
    int width = 5;

    for (int j = 0; j < size; j++)
    {
        // Print each number with a fixed width, centered within the width
        std::cout << std::setw(width) << test[j] << " ";
    }

    std::cout << "\n" << std::endl;
}

void Renderer::drawText(std::string text, std::string fontName, int fontSize, std::tuple<int, int> pos)
{
    // std::cout << text << std::endl;

}

std::tuple<int, int> Renderer::getResolution()
{
    return std::tuple<int,int>();
}