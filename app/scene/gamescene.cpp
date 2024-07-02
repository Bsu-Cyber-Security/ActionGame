#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QTextStream>
#include <QGraphicsSimpleTextItem>
#include <QPoint>
#include <QDir>
#include <cmath>
#include <map>

#include "app/scene/game_state.h"
#include "app/scene/gamescene.h"
#include "app/pixmap_manager/pixmap_manager.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
    , numberOfPlayers(2){
    setSceneRect(0,0, 800, 800);
    readLevelsFile("C:/Users/vtali/Documents/ActionGame/Resource/map.txt");
    drawMap();
    runLevel();
}

std::vector<std::vector<char>> map(20, std::vector<char>(20));
std::map<int, QPixmap> playerImages;

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
                    else if(map[i][j == '2']){
                        this->startCoord.setX(i);
                        this->startCoord.setY(j);
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
    std::vector<std::pair<QPoint, QString>> m_players(this->numberOfPlayers);

    //Инциализация игроков
    for(auto player : m_players)  {
        player.first = startCoord;
    }
    //Игровой цикл
    initializePlayerImages();
    drawPlayers(m_players);

    while(gameIsActive)
    {
        for(int playerIndex = 0; playerIndex < numberOfPlayers; ++playerIndex)
        {
            std::srand(time(0));
            int roll = std::rand()%6 + 1;

            if(m_players[playerIndex].first == this->endCoord)
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

void GameScene::drawMap(){
    QPixmap background ("C:/Users/vtali/Documents/ActionGame/Resource/2.jpg");
    // Создаем элемент для фона и устанавливаем его размер равным размеру сцены
    QGraphicsPixmapItem* backgroundItem = addPixmap(background.scaled(width(), height()));

    QPixmap road("C:/Users/vtali/Documents/ActionGame/Resource/road.jpg"); // Путь к изображению дорожки
    int tileSize = 40; // Размер одной плитки

            // Проходим по матрице карты и рисуем дорожки
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] != '0') {
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

void GameScene::initializePlayerImages() {
    // Инициализация изображений игроков
    playerImages[0] = QPixmap("C:/Users/vtali/Documents/ActionGame/Resource/ball.png");
    playerImages[1] = QPixmap("C:/Users/vtali/Documents/ActionGame/Resource/cloud.png");
}

void GameScene::drawPlayers(std::vector<std::pair<QPoint, QString>>& m_players) {
    // Получаем размер клетки
    const int cellSize = 40; // Пример размера клетки
    // Получаем количество игроков
    const int numPlayers = m_players.size();
    // Определяем размер картинок игроков
    int playerImageSize = cellSize / numPlayers;
    // Перебираем всех игроков
    for (size_t i = 0; i < numPlayers; ++i) {
        QPixmap playerPixmap = playerImages[i];
        // Масштабируем картинку до заданного размера
        playerPixmap = playerPixmap.scaled(playerImageSize, playerImageSize, Qt::KeepAspectRatio);
        // Создаем графический элемент для картинки игрока
        QGraphicsPixmapItem* playerItem = new QGraphicsPixmapItem(playerPixmap);
        // Вычисляем координаты для размещения картинки
        int x = startCoord.x() + i*playerImageSize;
        int y = startCoord.y();
        // Устанавливаем позицию графического элемента
        playerItem->setPos(x*39, y*39);
        // Устанавливаем выравнивание по верхнему краю
        // Добавляем графический элемент на сцену
        this->addItem(playerItem);
    }
}
