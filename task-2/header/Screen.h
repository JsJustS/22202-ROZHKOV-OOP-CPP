//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_SCREEN_H
#define TASK_2_SCREEN_H
/**
 * Interface for displaying current state
 * of the game.
 * */
#include <string>

// todo: screen
 class Screen {
 public:
     virtual ~Screen() = default;

     virtual Screen& setHeight(int h) = 0;
     virtual Screen& setWidth(int w) = 0;
     virtual int getHeight() = 0;
     virtual int getWidth() = 0;

     virtual Screen& addText(int x, int y, const std::string& text, int color) = 0;
     virtual Screen& addPixel(int x, int y, int color) = 0;
     virtual Screen& addLine(int x1, int y1, int x2, int y2, int color) = 0;
     virtual Screen& render() = 0;
     virtual Screen& clear() = 0;
 };
#endif //TASK_2_SCREEN_H
