//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_FIELD_H
#define TASK_2_FIELD_H

#include <vector>
#include <stdexcept>

/**
 * Contains current game state
 * */
class Field {
    int width;
    int height;
    bool *cells;
public:
    Field();

    Field(int w, int h);

    ~Field();

    void load(std::vector<std::pair<int, int>> coords);

    void setCell(int x, int y, bool isAlive);

    bool getCell(int x, int y);

    char countAliveNeighbours(int x, int y);

    std::string toString();

    friend void swap(Field& a, Field& b) {
        int aW = a.width;
        int aH = a.height;

        a.width = b.width;
        a.height = b.height;

        b.width = aW;
        b.height = aH;

        std::swap(a.cells, b.cells);
    }
};
#endif //TASK_2_FIELD_H
