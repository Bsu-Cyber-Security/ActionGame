#pragma once

#include <QGraphicsScene>
#include <QElapsedTimer>
#include <QTimer>

#include "level.h"


class GameScene : public QGraphicsScene {
    Q_OBJECT
   public:
    explicit GameScene(QObject *parent = nullptr);

   signals:

   private slots:
    void loop();

   private:
    Level m_level;
    bool m_mapNeedRedraw;
    bool m_levelIsCompleted;
    int m_cameraOffsetX;
    int m_cameraOffsetY;

    // Time controll
    const int FPS = 60;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    float m_deltaTime = 0.0f, m_loopTime = 0.0f;
    const float m_loopSpeed = int(1000.0f/FPS);

   protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
