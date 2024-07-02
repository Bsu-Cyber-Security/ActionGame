#pragma once

#include "qgraphicsitem.h"
#include "QGraphicsScene"
#include <QElapsedTimer>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

// Убедитесь, что вы включили все необходимые заголовочные файлы для QWidget

class GameScene : public QGraphicsScene {
    Q_OBJECT
   public:
    explicit GameScene(QObject *parent = nullptr);
     short numberOfPlayers;

   private:
    void resetStatus();
    void readLevelsFile(QString pathFile);
    void runLevel();
    void drawMap();
    void drawPlayers(std::vector<std::pair<QPoint, QString>>&);
    void initializePlayerImages();
    void showDiceAnimation();
    QWidget* buttonWindow;
    QLabel* diceLabel = nullptr; // Лейбл для анимации
    QVBoxLayout* mainLayout;


    QPoint endCoord;
    QPoint startCoord;

    QPushButton* button = new QPushButton("Click me");

    bool gameIsActive;
   private slots:
    void Click();


};
