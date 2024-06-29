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
    //connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    //m_timer.start(int(1000.0f/FPS));
    m_elapsedTimer.start();
}
