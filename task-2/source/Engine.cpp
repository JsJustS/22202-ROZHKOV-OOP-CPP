//
// Created by Just on 18.11.2023.
//
#include "../header/Engine.h"

#define MIN_WINDOW_WIDTH 30
#define MIN_WINDOW_HEIGHT 7

Engine* Engine::instance = nullptr;

Engine::Engine() {
    this->inputManager = nullptr;
    this->field = nullptr;
    this->fieldOld = nullptr;
    this->config = nullptr;
    this->logger = nullptr;
    this->screen = nullptr;

    this->exitcode = false;
    this->needsScreenUpdate = false;

    this->generation = 0;
}

void Engine::init() {;
    instance = new Engine();
    instance->screen = new ConsoleScreen(30, 5);
    instance->inputManager = new InputManager();

    Input* inputType = new ConsoleInput();
    instance->inputManager->setInputType((*inputType));
}

void Engine::stop() {
    delete instance->config;
    delete instance->field;
    delete instance->fieldOld;
    delete instance->screen;
    delete instance->inputManager;
    delete instance;
    instance = nullptr;
}

void Engine::loadConfig(const std::string &filename) {
    instance->config = new ConfigManager();
    std::vector<std::pair<int, int>> coords;

    if (filename.empty()) {
        std::string randFile = Engine::getRandomConfig();
        Engine::log("No config provided, using \"" + randFile + "\" from \"\\examples\".");
        coords = instance->config->load(Engine::getGameDir() + "\\examples\\" + randFile);
    } else {
        coords = instance->config->load(filename);
    }


    int fw = instance->config->getFieldWidth();
    int fh = instance->config->getFieldHeight();

    instance->field = new Field(fw,fh);
    instance->fieldOld = new Field(fw,fh);

    instance->field->load(coords);

    int w = (MIN_WINDOW_WIDTH > 2*fw + 3) ? MIN_WINDOW_WIDTH : 2*fw + 3;
    int h = (MIN_WINDOW_HEIGHT > fh + 6) ? MIN_WINDOW_HEIGHT : fh + 6;
    instance->screen->setWidth(w).setHeight(h);
}

std::string Engine::getRandomConfig() {
    std::vector<std::string> filenames{};

    WIN32_FIND_DATA ffd;
    TCHAR szDir[MAX_PATH];
    StringCchCopy(szDir, MAX_PATH, Engine::getGameDir().data());
    StringCchCat(szDir, MAX_PATH, TEXT("\\examples\\*"));
    HANDLE hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind) {
        return {};
    }

    do {
        std::string filename = std::string(ffd.cFileName);
        if (filename != "." && filename != "..") {
            filenames.push_back(filename);
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);

    const auto p1 = std::chrono::system_clock::now();
    long long seconds = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();

    return filenames[seconds % filenames.size()];
}

bool Engine::dump(const std::string &filenamelong) {
    std::string filename{};
    if (filenamelong.rfind('.') != std::string::npos) {
        int c = filenamelong.rfind('.');
        std::string suffix = filenamelong.substr(c, filenamelong.length() - c);
        filename = filenamelong.substr(0, c);
        if (suffix != ".lif" && suffix != ".life") {
            Engine::log("Wrong Format! using standard .lif");
        }
    } else {
        filename = filenamelong;
    }
    FileWriter writer(filename + ".lif");

    writer.open();
    if (!writer.isOpen()) {
        Engine::log("Could not open file.");
        return false;
    }

    writer.writeLine("#Life " + instance->config->getFileFormat());
    writer.writeLine("#N " + instance->config->getUniverseName());
    writer.writeLine("#S " + std::to_string(instance->config->getFieldWidth()) + "/" +
                        std::to_string(instance->config->getFieldHeight()));
    writer.writeLine("#R " + instance->config->getRulesAsString());

    int width = instance->config->getFieldWidth();
    int height = instance->config->getFieldHeight();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (instance->field->getCell(x, y)) {
                writer.writeLine(std::to_string(x) + " " + std::to_string(y));
            }
        }
    }

    writer.close();
    return true;
}

void Engine::setLogger(std::ostream &out) {
    delete instance->logger;
    instance->logger = &out;
}

void Engine::log(const std::string &message) {
    if (instance->logger == nullptr) return;
    (*instance->logger) << message << std::endl;
}

void Engine::clearScreen() {
    instance->screen->clear();
}

void Engine::drawGUI(int textColor, int barrierColor) {
    int textX = (instance->screen->getWidth() - instance->config->getUniverseName().length()) / 2;
    if (textX < 0) {
        textX = 0;
    }
    instance->screen->addText(textX, 1,
                              instance->config->getUniverseName(),
                              textColor);
    instance->screen->addLine(0, 0,
                              instance->screen->getWidth() - 1, 0,
                              barrierColor);

    std::string genText = "GEN: " + std::to_string(instance->generation);
    textX = (instance->screen->getWidth() - genText.length()) / 2;
    if (textX < 0) {
        textX = 0;
    }
    instance->screen->addText(textX, instance->screen->getHeight()-2,
                              genText,
                              textColor);

    std::string ruleText = instance->config->getRulesAsString();
    textX = (instance->screen->getWidth() - ruleText.length()) / 2;
    if (textX < 0) {
        textX = 0;
    }
    instance->screen->addText(textX, instance->screen->getHeight()-1,
                              ruleText,
                              textColor);
}

void Engine::drawField(int aliveColor, int deadColor, int barrierColor) {
    int width = instance->config->getFieldWidth();
    int height = instance->config->getFieldHeight();

    int deltaX = (instance->screen->getWidth() - 2*width - 3) / 2;
    if ((instance->screen->getWidth() - 2*width - 3 - deltaX) < deltaX) {
        deltaX += 1;
    }

    instance->screen->addLine(deltaX, 2,
                              deltaX + 2*width + 2, 2,
                              barrierColor);
    instance->screen->addLine(deltaX + 2*width + 2, 2,
                              deltaX + 2*width + 2, instance->screen->getHeight() - 3,
                              barrierColor);
    instance->screen->addLine(deltaX + 2*width + 2, instance->screen->getHeight() - 3,
                              deltaX, instance->screen->getHeight() - 3,
                              barrierColor);
    instance->screen->addLine(deltaX, instance->screen->getHeight() - 3,
                              deltaX, 2,
                              barrierColor);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            instance->screen->addPixel(2*x+2+deltaX, y+3,(instance->field->getCell(x, y)) ? aliveColor : deadColor);
        }
    }
}

void Engine::drawText(int x, int y, const std::string& text, int textColor) {
    instance->screen->addText(x, y, text, textColor);
}

void Engine::drawScreen() {
    instance->screen->render();
}

void Engine::tickField() {
    int width = instance->config->getFieldWidth();
    int height = instance->config->getFieldHeight();

    (*instance->fieldOld) = (*instance->field);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char count = instance->fieldOld->countAliveNeighbours(x, y);
            bool shouldBirth = instance->config->canBirth(count);
            bool shouldSurvive = instance->config->canSurvive(count);

            if (instance->fieldOld->getCell(x, y)) {
                instance->field->setCell(x, y, shouldSurvive);
            } else {
                instance->field->setCell(x, y, shouldBirth);
            }

        }
    }

    instance->generation++;
}

std::string Engine::getGameDir() {
    return "games";
}

void Engine::startOnline() {
    Engine::log("Press ENTER to start!");

    int barrierColor = ConsoleScreen::rgb2Int(13, 77, 0);
    int textColor = ConsoleScreen::rgb2Int(0, 255, 255);
    int aliveCellColor = ConsoleScreen::rgb2Int(255, 255, 255);
    int deadCellColor = ConsoleScreen::rgb2Int(0, 0, 0);

    while (!instance->exitcode) {
        if (Engine::shouldScreenUpdate()) {
            Engine::clearScreen();
            Engine::drawGUI(textColor, barrierColor);
            Engine::drawField(aliveCellColor, deadCellColor, barrierColor);
            Engine::drawScreen();
            Engine::setScreenUpdate(false);
        }

        Engine::tickUserInput();
    }
}

void Engine::tickUserInput() {
    instance->inputManager->processActions();
}

void Engine::setExit(bool code) {
    instance->exitcode = code;
}

bool Engine::shouldScreenUpdate() {
    return instance->needsScreenUpdate;
}

void Engine::setScreenUpdate(bool bl) {
    instance->needsScreenUpdate = bl;
}
