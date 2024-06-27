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

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_mapNeedRedraw(false)
    , m_levelIsCompleted(false)
    , m_cameraOffsetX(0)
    , m_cameraOffsetY(0) {
    setSceneRect(0,0, 640, 480);
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(1000.0f/FPS));
    m_elapsedTimer.start();
}


void GameScene::loop() {
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    if( m_loopTime > m_loopSpeed)
    {
        m_loopTime -= m_loopSpeed;

        handlePlayerInput();
        if(m_mapNeedsRedraw)
        {
            clear();
            drawMap();
            if(m_levelIsCompleted)
            {
                QRect screenRect = QRect(SCREEN::HALF_WIDTH/2-m_cameraOffsetX,SCREEN::HALF_WIDTH/4-m_cameraOffsetY,SCREEN::HALF_WIDTH/2, SCREEN::HALF_WIDTH/2);
                drawTilemap(screenRect, PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::Solved));
            }
            drawCurentLevelStatus();
            m_mapNeedsRedraw = false;
        }
        resetStatus();
    }
}
