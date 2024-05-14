#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QGraphicsSimpleTextItem>
#include <QPainter>
#include <QDir>

#include "app/include/gamescene.h"
#include "app/include/pixmapmanager.h"
#include "app/include/game_state.h"

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
