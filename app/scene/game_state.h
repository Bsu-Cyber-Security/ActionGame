#pragma once

#include <QPoint>
#include <QList>

struct GameState {
    QPoint player;
    int score;

    GameState() : score(0) {
    }
};
