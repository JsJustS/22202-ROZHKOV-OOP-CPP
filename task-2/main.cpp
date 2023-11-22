//
// Created by Just on 22.11.2023.
//
#include "header/Engine.h"

#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
    std::chrono::milliseconds timespan(1000); // or whatever

    Engine::init();
    Engine::setLogger(std::cout);
    Engine::loadConfig("C:\\Users\\Just\\CLionProjects\\22202-ROZHKOV-OOP-CPP\\task-2\\games\\test.lif");

    Engine::draw(); // ask Screen to draw current Field on itself

    while (true) {
        Engine::tick();
        Engine::draw();
        std::this_thread::sleep_for(timespan);
    }

    Engine::stop();
    return 0;
}