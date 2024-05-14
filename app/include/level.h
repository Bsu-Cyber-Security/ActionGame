#pragma once

#include <QList>
#include <QChar>
#include <QPoint>

#include "game_state.h"

struct Cell;

struct Level {
    int width;
    int height;
    QList<QList<Cell>> map;
    GameState startState;
};
