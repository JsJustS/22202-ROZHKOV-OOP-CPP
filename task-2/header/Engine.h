//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_ENGINE_H
#define TASK_2_ENGINE_H
/**
 * Main class for the game
 * */
#include "Executor.h"

#include <iostream>
#include <utility>
#include <chrono>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "Field.h"
#include "ConfigManager.h"
#include "Screen.h"
#include "ConsoleScreen.h"
#include "ConsoleInput.h"
#include "InputManager.h"
#include "FileWriter.h"

class Engine : public Executor {
private:
    Field* field;
    Field* fieldOld;
    ConfigManager* config;
    Screen* screen;
    InputManager* inputManager;

    std::ostream* logger;

    bool exitcode;
    bool needsScreenUpdate;

    int generation;
public:
    static std::string getGameDir();

    Engine();

    Engine(Engine const&) = delete;
    void operator=(Engine const&) = delete;

    void startOnline();
    void stop();
    void init();

    void setExit(bool code);
    void setLogger(std::ostream& out);
    void log(const std::string &message);

    void loadConfig(const std::string& filename = "");
    static std::string getRandomConfig();
    bool dump(const std::string& filename);

    void clearScreen();
    void drawGUI(int textColor, int barrierColor);
    void drawField(int aliveColor, int deadColor, int barrierColor);
    void drawText(int x, int y, const std::string& text, int textColor);
    void drawScreen();

    bool shouldScreenUpdate() const;
    void setScreenUpdate(bool bl);

    void tickField() override;
    void tickUserInput();
};
#endif //TASK_2_ENGINE_H
