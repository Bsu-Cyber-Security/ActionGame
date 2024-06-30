#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QGraphicsSimpleTextItem>
#include <QPainter>
#include <QDir>

#include "app/scene/game_state.h"
#include "app/scene/gamescene.h"
#include "app/pixmap_manager/pixmap_manager.h"

void GameScene::readLevelsFile(QString pathFile)
{
    std::vector<std::vector<char>> map(20, std::vector<char>(20));

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

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_mapNeedRedraw(false)
    , m_levelIsCompleted(false)
    , m_cameraOffsetX(0)
    , m_cameraOffsetY(0) {
    setSceneRect(0,0, 640, 480);
    //connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    //m_timer.start(int(1000.0f/FPS));
    m_elapsedTimer.start();
}
