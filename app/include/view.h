#pragma once

#include <QGraphicsView>
#include "gamescene.h"

enum class ViewDirection{
    None,
    Up,
    Down,
    Left,
    Right
};

class View : public QGraphicsView {
    Q_OBJECT
   public:
    explicit View();

   signals:

   private:
    GameScene* m_gameScene;
    ViewDirection m_dir;

   protected:
    // QWidget interface
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

    // QAbstractScrollArea interface
    virtual void scrollContentsBy(int dx, int dy) override;

};
