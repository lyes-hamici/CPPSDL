#ifndef RENDERER_H
#define RENDERER_H

#include <tuple>
#include <vector>
#include <string>

class Renderer
{
private:
public:
    static void initialize();
    static void destroy();
    static void clear();
    static void loadTextures();
    static void loadFont();
    static void draw();
    static void drawRow(void * row, int size);
    static void drawText(std::string text, std::string fontName, int fontSize, std::tuple<int,int> pos);
    static std::tuple<int,int> getResolution();
};

#endif