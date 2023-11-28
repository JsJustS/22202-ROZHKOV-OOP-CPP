//
// Created by Just on 18.11.2023.
//
#include "../header/Engine.h"

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
    this->screen = new ConsoleScreen(30, 5);
    this->inputManager = new InputManager();

    Input* inputType = new ConsoleInput();
    this->inputManager->setInputType((*inputType));
}

void Engine::stop() {
    delete this->config;
    delete this->field;
    delete this->fieldOld;
    delete this->screen;
    delete this->inputManager;
}

void Engine::loadConfig(const std::string &filename) {
    this->config = new ConfigManager();
    std::vector<std::pair<int, int>> coords;

    if (filename.empty()) {
        std::string randFile = Engine::getRandomConfig();
        Engine::log("No config provided, using \"" + randFile + "\" from \"\\examples\".");
        coords = this->config->load(Engine::getGameDir() + "\\examples\\" + randFile);
    } else {
        coords = this->config->load(filename);
    }

    this->config->setLogger(*this->logger);

    int fw = this->config->getFieldWidth();
    int fh = this->config->getFieldHeight();

    this->field = new Field(fw,fh);
    this->fieldOld = new Field(fw,fh);

    this->field->load(coords);

    int w = (MIN_WINDOW_WIDTH > 2*fw + 3) ? MIN_WINDOW_WIDTH : 2*fw + 3;
    int h = (MIN_WINDOW_HEIGHT > fh + 6) ? MIN_WINDOW_HEIGHT : fh + 6;
    this->screen->setWidth(w).setHeight(h);
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
    if (filenamelong.rfind('.') == std::string::npos) {
        filename = filenamelong + ".lif";
    } else {
        filename = filenamelong;
    }
    FileWriter writer(filename);

    writer.open();
    if (!writer.isOpen()) {
        Engine::log("Could not open file.");
        return false;
    }

    writer.writeLine("#Life " + this->config->getFileFormat());
    writer.writeLine("#N " + this->config->getUniverseName());
    writer.writeLine("#S " + std::to_string(this->config->getFieldWidth()) + "/" +
                        std::to_string(this->config->getFieldHeight()));
    writer.writeLine("#R " + this->config->getRulesAsString());

    int width = this->config->getFieldWidth();
    int height = this->config->getFieldHeight();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (this->field->getCell(x, y)) {
                writer.writeLine(std::to_string(x) + " " + std::to_string(y));
            }
        }
    }

    writer.close();
    return true;
}

void Engine::setLogger(std::ostream &out) {
    this->logger = &out;
}

void Engine::log(const std::string &message) {
    if (this->logger == nullptr) return;
    (*this->logger) << message << std::endl;
}

void Engine::clearScreen() {
    this->screen->clear();
}

void Engine::drawGUI(int textColor, int barrierColor) {
    int textX = (this->screen->getWidth() - this->config->getUniverseName().length()) / 2;
    if (textX < 0) {
        textX = 0;
    }
    this->screen->addText(textX, 1,
                          this->config->getUniverseName(),
                          textColor);
    this->screen->addLine(0, 0,
                          this->screen->getWidth() - 1, 0,
                          barrierColor);

    std::string genText = "GEN: " + std::to_string(this->generation);
    textX = (this->screen->getWidth() - genText.length()) / 2;
    if (textX < 0) {
        textX = 0;
    }
    this->screen->addText(textX, this->screen->getHeight()-2,
                              genText,
                              textColor);

    std::string ruleText = this->config->getRulesAsString();
    textX = (this->screen->getWidth() - ruleText.length()) / 2;
    if (textX < 0) {
        textX = 0;
    }
    this->screen->addText(textX, this->screen->getHeight()-1,
                              ruleText,
                              textColor);
}

void Engine::drawField(int aliveColor, int deadColor, int barrierColor) {
    int width = this->config->getFieldWidth();
    int height = this->config->getFieldHeight();

    int deltaX = (this->screen->getWidth() - 2*width - 3) / 2;
    if ((this->screen->getWidth() - 2*width - 3 - deltaX) < deltaX) {
        deltaX += 1;
    }

    this->screen->addLine(deltaX, 2,
                              deltaX + 2*width + 2, 2,
                              barrierColor);
    this->screen->addLine(deltaX + 2*width + 2, 2,
                              deltaX + 2*width + 2, this->screen->getHeight() - 3,
                              barrierColor);
    this->screen->addLine(deltaX + 2*width + 2, this->screen->getHeight() - 3,
                              deltaX, this->screen->getHeight() - 3,
                              barrierColor);
    this->screen->addLine(deltaX, this->screen->getHeight() - 3,
                              deltaX, 2,
                              barrierColor);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            this->screen->addPixel(2*x+2+deltaX, y+3,(this->field->getCell(x, y)) ? aliveColor : deadColor);
        }
    }
}

void Engine::drawText(int x, int y, const std::string& text, int textColor) {
    this->screen->addText(x, y, text, textColor);
}

void Engine::drawScreen() {
    this->screen->render();
}

void Engine::tickField() {
    int width = this->config->getFieldWidth();
    int height = this->config->getFieldHeight();

    (*this->fieldOld) = (*this->field);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char count = this->fieldOld->countAliveNeighbours(x, y);
            bool shouldBirth = this->config->canBirth(count);
            bool shouldSurvive = this->config->canSurvive(count);

            if (this->fieldOld->getCell(x, y)) {
                this->field->setCell(x, y, shouldSurvive);
            } else {
                this->field->setCell(x, y, shouldBirth);
            }

        }
    }

    this->generation++;
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

    while (!this->exitcode) {
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
    // fetch all inputs for current tick from user (Commands, Keyboard, Touchscreen, etc...)
    // todo: finish
    this->inputManager->tick();
    std::vector<Action> userActions = this->inputManager->getAllUserInputs();
    for (Action& action : userActions) {
        ActionResult result = action.act();

        bool isTickConsumed = false;
        switch (result) {
            case CONSUME:
                isTickConsumed = true;
                break;
            case TERMINATE:
                this->setExit(true);
                isTickConsumed = true;
                break;
            case PASS:
            default:
                break;
        }

        if (isTickConsumed) {
            break;
        }
    }
}

void Engine::setExit(bool code) {
    this->exitcode = code;
}

bool Engine::shouldScreenUpdate() const {
    return this->needsScreenUpdate;
}

void Engine::setScreenUpdate(bool bl) {
    this->needsScreenUpdate = bl;
}
