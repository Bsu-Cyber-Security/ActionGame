#include "app/view/view.h"

View::View()
    : m_gameScene(new GameScene(this))
    , m_dir(ViewDirection::None) {
    setScene(m_gameScene);
    resize(m_gameScene->sceneRect().width()+2, m_gameScene->sceneRect().height()+2);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::NoFocus);
}

void View::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape) {
        QApplication::instance()->quit();
    } else {
        m_dir == ViewDirection::None;
    }
    QGraphicsView::keyPressEvent(event);
}

void View::scrollContentsBy(int dx, int dy) {
    if(m_dir != ViewDirection::None) {
        QGraphicsView::scrollContentsBy(dx, dy);
    }
}
