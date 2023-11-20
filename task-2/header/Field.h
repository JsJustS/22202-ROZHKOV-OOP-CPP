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
     // todo: Field logic
     // Field should not calculate anything, it's just a container for current game state
     int width;
     int height;
     bool* cells;
 public:
     Field();
     ~Field();
     void init(int w, int h, std::vector<std::pair<int, int>> coords);
     void setCell(int x, int y, bool isAlive);
     bool getCell(int x, int y);
     std::string toString();
 };
#endif //TASK_2_FIELD_H
