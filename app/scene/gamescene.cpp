#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QGraphicsSimpleTextItem>
#include <QPainter>
#include <QDir>
#include "QPainter"

#include "app/scene/game_state.h"
#include "app/scene/gamescene.h"
#include "app/pixmap_manager/pixmap_manager.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
    , numberOfPlayers(0){
    setSceneRect(0,0, 800, 800);
    readLevelsFile("C:/Users/vtali/Documents/ActionGame/Resource/map.txt");
    drawMap();
    runLevel();
}

std::vector<std::vector<char>> map(20, std::vector<char>(20));

void GameScene::readLevelsFile(QString pathFile)
{

    QFile file(pathFile);

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);

        for (int i = 0; i < 20; ++i)
        {
            QString line = in.readLine();
            QStringList cells = line.split(' ');

            if (cells.size() == 20)
            {
                for (int j = 0; j < 20; ++j)
                {
                    map[i][j] = cells[j].toLatin1()[0];
                    if(map[i][j] == '3'){
                        this->endCoord.setX(i);
                        this->endCoord.setY(j);
                    }
                }
            }

            else
            {
                qDebug() << "Error: Invalid map data in line" << i + 1;
            }
        }

        file.close();
    }
    else
    {
        qDebug() << "Error: Failed to open file" << pathFile;
    }
}

void GameScene::runLevel(){
    while(gameIsActive)
    {
        for(int playerIndex = 0; playerIndex < numberOfPlayers; ++playerIndex)
        {
            std::srand(time(0));
            int roll = std::rand()%6 + 1;

            if(inTheEnd(playerIndex))
            {
                gameIsActive = false; // Завершаем игру
                break; // Выходим из цикла
            }
            else
            {
                //updatePlayerStatus(playerIndex); // Обновляем статус текущего игрока
                //drawBoard(playerIndex); // Перерисовываем доску для текущего игрока
            }

                //resetStatus(playerIndex); // Сбрасываем статус для следующего обновления цикла
        }
    }
}

bool GameScene::inTheEnd(int playerIndex){
    return this->endCoord == m_players[playerIndex];
}

void GameScene::drawMap(){
    QPixmap background("C:/Users/vtali/Documents/ActionGame/Resource/2.jpg");
    // Создаем элемент для фона и устанавливаем его размер равным размеру сцены
    QGraphicsPixmapItem* backgroundItem = addPixmap(background.scaled(width(), height()));

    QPixmap road("C:/Users/vtali/Documents/ActionGame/Resource/road.jpg"); // Путь к изображению дорожки
    int tileSize = 40; // Размер одной плитки

            // Проходим по матрице карты и рисуем дорожки
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == '1') {
                QGraphicsPixmapItem* roadItem = new QGraphicsPixmapItem(road);
                // Устанавливаем размер плитки дорожки
                roadItem->setPixmap(road.scaled(tileSize, tileSize));
                // Устанавливаем позицию элемента дорожки
                roadItem->setPos(j * tileSize, i * tileSize);
                // Добавляем элемент дорожки в сцену
                addItem(roadItem);
            }
        }
    }
}
