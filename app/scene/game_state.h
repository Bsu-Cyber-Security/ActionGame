#pragma once

#include <QPoint>
#include <QList>

struct GameState {
    QPoint player;
    int steps;

    GameState() : steps(0) {
    }
};
