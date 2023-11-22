//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_SCREEN_H
#define TASK_2_SCREEN_H
/**
 * Interface for displaying current state
 * of the game.
 * */
 // todo: screen
 class Screen {
 public:
     virtual ~Screen() = default;
     // A pure virtual method is a class method that is defined as virtual and assigned to 0.
     virtual void OverrideMe() = 0;
 };
#endif //TASK_2_SCREEN_H
