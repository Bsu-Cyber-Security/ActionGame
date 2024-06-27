#pragma once

#include <QPoint>
#include <QList>

struct GameState {
    Qpoint player;
    int score;

    GameState() : score(0) {
    }
};
