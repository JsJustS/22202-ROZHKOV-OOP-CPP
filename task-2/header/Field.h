//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_FIELD_H
#define TASK_2_FIELD_H

#include <vector>

/**
 * Processes current game state
 * */
 class Field {
 public:
     void load(std::vector<std::pair<int, int>> coords);
     void setCell(int x, int y, bool isAlive);
 };
#endif //TASK_2_FIELD_H
