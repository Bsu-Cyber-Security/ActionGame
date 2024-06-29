#pragma once
#include <QList>
#include "app/scene/game_state.h"
//Предварительно
struct Level{
    int width;
    int height;
    QList<QList<QChar>> object_map;
    GameState gameState;
};
