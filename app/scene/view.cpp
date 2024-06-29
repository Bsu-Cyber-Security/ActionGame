#include "view.h"

View::View()
    : m_gameScene(new GameScene(this)),
    m_left(false), m_right(false), m_up(false), m_down(false)
{
    setScene(m_gameScene);
    // Устанавливаем размер представления равным размеру сцены без дополнительных отступов
    resize(m_gameScene->sceneRect().size().toSize());

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::NoFocus);
}
