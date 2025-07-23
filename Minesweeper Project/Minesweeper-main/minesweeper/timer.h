//
// Created by carlo on 4/11/2024.
//

#ifndef MINESWEEPER_TIMER_H
#define MINESWEEPER_TIMER_H

#endif //MINESWEEPER_TIMER_H

#include <vector>
#include <string>
#include <string.h>
#include <cstdlib>
#include <SFML/System/Clock.hpp>
using namespace std;
using namespace sf;
struct Timer {
    Clock main;
    float time;
    bool paused;
    Timer() {
        paused = false;
        time = 0;
        main.restart();
    }
    void resume() {
        if (paused) {
            main.restart();
        }
        paused = false;
    }
    void pause() {
        if (!paused) {
            time += main.getElapsedTime().asSeconds();
        }
        paused = true;
    }
    void reset() {
        main.restart();
        time = 0;
        paused = false;
    }
    float gettotalseconds() {
        if (!paused) {
            return time + main.getElapsedTime().asSeconds();
        }
        return time;
    }
};

