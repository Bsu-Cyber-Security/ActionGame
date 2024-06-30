#pragma once

#include "qgraphicsitem.h"
#include "QGraphicsScene"
#include <QElapsedTimer>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <vector>

// Убедитесь, что вы включили все необходимые заголовочные файлы для QWidget

class GameScene : public QGraphicsScene {
    Q_OBJECT
   public:
    explicit GameScene(QObject *parent = nullptr);

   private:
    void handlePlayerInput();
    void resetStatus();
    void readLevelsFile(QString pathFile);
    void runLevel();
    void drawMap();
    void drawCurentLevelStatus();
    void renderGameScene();
    bool inTheEnd(int);

    QPoint endCoord;

    bool gameIsActive;
    short numberOfPlayers;

    std::vector<QPoint> m_players;
};
