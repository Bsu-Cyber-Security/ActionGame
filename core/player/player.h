#pragma once
#include <string>
#include <vector>
#include <QPoint>

struct Player{
    std::vector<QPoint> coordinates;
    int current_pos;
    std::string nickname;
};
