//
// Created by Just on 18.11.2023.
//

#ifndef TASK_2_ENGINE_H
#define TASK_2_ENGINE_H
/**
 * Main class for the game
 * */
#include <iostream>
#include <utility>
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

class Engine {
private:
    static Engine* instance;

    Field* field;
    Field* fieldOld;
    ConfigManager* config;
    Screen* screen;
    InputManager* inputManager;

    std::ostream* logger;

    bool exitcode;
    bool needsScreenUpdate;

    int generation;

    Engine();
public:
    static std::string getGameDir();

    Engine(Engine const&) = delete;
    void operator=(Engine const&) = delete;

    static void startOnline();
    static void stop();
    static void init();

    static void setExit(bool code);
    static void setLogger(std::ostream& out);
    static void log(const std::string &message);

    static void loadConfig(const std::string& filename = "");
    static std::string getRandomConfig();
    static bool dump(const std::string& filename);

    static void clearScreen();
    static void drawGUI(int textColor, int barrierColor);
    static void drawField(int aliveColor, int deadColor, int barrierColor);
    static void drawText(int x, int y, const std::string& text, int textColor);
    static void drawScreen();

    static bool shouldScreenUpdate();
    static void setScreenUpdate(bool bl);

    static void tickField();
    static void tickUserInput();
};
#endif //TASK_2_ENGINE_H
