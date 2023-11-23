//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_CONSOLESCREEN_H
#define TASK_2_CONSOLESCREEN_H
/**
 * Extends "Screen.h".
 * Displays game state in the console
 * */

/**
Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107
 * */
#include "Screen.h"
#include <iostream>

//todo: ConsoleScreen
 class ConsoleScreen : public Screen {
 private:
     int width;
     int height;
     std::string* pixels;
 public:

     ConsoleScreen();
     ConsoleScreen(int w, int h);
     ~ConsoleScreen() override;

     Screen& setHeight(int h) override;
     Screen& setWidth(int w) override;
     int getHeight() override;
     int getWidth() override;

     Screen& addText(int x, int y, const std::string& text, int color) override;
     Screen& addPixel(int x, int y, int color) override;
     Screen& addLine(int x1, int y1, int x2, int y2, int color) override;

     Screen& render() override;
     Screen& clear() override;

     static int rgb2Int(int r, int g, int b);
     static std::string rgb2Str(int r, int g, int b);
 };
#endif //TASK_2_CONSOLESCREEN_H
