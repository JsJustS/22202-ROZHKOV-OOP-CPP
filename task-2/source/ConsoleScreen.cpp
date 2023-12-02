//
// Created by Just on 18.11.2023.
//
#include "../header/ConsoleScreen.h"

ConsoleScreen::ConsoleScreen() {
    this->width = 0;
    this->height = 0;
    this->pixels = nullptr;
}

ConsoleScreen::ConsoleScreen(int w, int h) {
    this->width = w;
    this->height = h;
    this->pixels = nullptr;
}

ConsoleScreen::~ConsoleScreen() {
    delete [] this->pixels;
}

Screen& ConsoleScreen::render() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            std::cout << this->pixels[i*this->width + j];
        }
        std::cout << std::endl;
    }
    return *this;
}

Screen& ConsoleScreen::clear() {
    if (this->width < 0 && this->height < 0) {throw std::runtime_error("Trying to clear Screen which is not set.");}
    if (this->pixels == nullptr) {
        this->pixels = new std::string[this->width*this->height];
    }

    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            this->pixels[i*this->width + j] = " ";
        }
    }
    system("cls");
    return *this;
}

Screen& ConsoleScreen::setHeight(int h) {
    this->height = h;
    return *this;
}

Screen& ConsoleScreen::setWidth(int w) {
    this->width = w;
    return *this;
}

int ConsoleScreen::getHeight() {
    return this->height;
}

int ConsoleScreen::getWidth() {
    return this->width;
}

Screen& ConsoleScreen::addText(int x, int y, const std::string &text, int color) {
    if (x < 0 || x + 1 > this->width || y < 0 || y + 1 > this->height) return *this;
    int len = (text.length() < (this->width - x)) ? text.length() : this->width - x;
    for (int i = 0; i < len; ++i) {
        int red = (color >> 16) & 0xFF;
        int green = (color >> 8) & 0xFF;
        int blue = color & 0xFF;
        this->pixels[y*this->getWidth() + x + i] = ConsoleScreen::rgb2Str(red, green, blue) + text[i] + "\033[0m";
    }
    return *this;
}

Screen& ConsoleScreen::addPixel(int x, int y, int color) {
    if (x < 0 || x + 1 > this->width || y < 0 || y + 1 > this->height) return *this;
    int red = (color >> 16) & 0xFF;
    int green = (color >> 8) & 0xFF;
    int blue = color & 0xFF;
    this->pixels[y*this->getWidth() + x] = ConsoleScreen::rgb2Str(red, green, blue) + "#\033[0m";
    return *this;
}

int ConsoleScreen::rgb2Int(int r, int g, int b) {
    int rgb = r;
    rgb = (rgb << 8) + g;
    return (rgb << 8) + b;
}

std::string ConsoleScreen::rgb2Str(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

Screen &ConsoleScreen::addLine(int x1, int y1, int x2, int y2, int color) {
    if (x1 > x2 || y1 > y2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    bool invert = false;
    if (y1 - y2 < x1 - x2) {
        invert = true;
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    double k = ((double)y1 - y2) / (x1 - x2);
    double b = y1 - k*x1;
    int step = x1 < x2 ? 1 : -1;

    int temp_x = x1;
    int temp_y = y1;
    while (temp_x != x2 || temp_y != y2) {
        if (invert) {
            this->addPixel(temp_y, temp_x, color);
        } else {
            this->addPixel(temp_x, temp_y, color);
        }
        temp_x += step;
        double dy = k*temp_x + b;
        temp_y = dy < (int)dy + 0.5? (int)dy : (int)dy + 1;
    }
    if (invert) {
        this->addPixel(temp_y, temp_x, color);
    } else {
        this->addPixel(temp_x, temp_y, color);
    }
    return *this;
}
