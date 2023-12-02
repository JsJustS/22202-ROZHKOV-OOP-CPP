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

    Field& operator= (const Field& other);
};
#endif //TASK_2_FIELD_H
