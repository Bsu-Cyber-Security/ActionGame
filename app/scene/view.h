#pragma once

#include <QGraphicsView>
#include "gamescene.h"

class View : public QGraphicsView
{
    Q_OBJECT
   public:
    explicit View();

   private:
    GameScene* m_gameScene;
    bool m_left, m_right, m_up, m_down;
};
