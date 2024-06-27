#pragma once

#include <QPoint>
#include <QList>

struct GameState {
    Player player;
    Level level;
    int score;

    GameState() : score(0) {
    }
};
