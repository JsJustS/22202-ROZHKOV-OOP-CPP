//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_CONSOLESCREEN_H
#define TASK_2_CONSOLESCREEN_H
#include "Screen.h"
#include <iostream>

class ConsoleScreen : public Screen {
private:
    int width;
    int height;
    std::string *pixels;
public:

    ConsoleScreen();
    ConsoleScreen(int w, int h);
    ~ConsoleScreen() override;

    Screen &setHeight(int h) override;
    Screen &setWidth(int w) override;

    int getHeight() override;
    int getWidth() override;

    Screen &addText(int x, int y, const std::string &text, int color) override;
    Screen &addPixel(int x, int y, int color) override;
    Screen &addLine(int x1, int y1, int x2, int y2, int color) override;

    Screen &render() override;
    Screen &clear() override;

    static int rgb2Int(int r, int g, int b);
    static std::string rgb2Str(int r, int g, int b);
};
#endif //TASK_2_CONSOLESCREEN_H
