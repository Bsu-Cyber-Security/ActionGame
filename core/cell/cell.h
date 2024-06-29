#pragma once
#include <iostream>
#include <string>
#include <QPixmap>

class Cell
{
   private:
    int m_x = 0;
    int m_y = 0;
    int m_width = 0;
    int m_height = 0;
    bool m_CanMove = true;
    QPixmap m_image;
   public:
    Cell()= default;
    Cell(int x, int y, int width, int height, bool CanMove,  QPixmap& image): m_x(x), m_y(y), m_width(width), m_height(height), m_CanMove(CanMove), m_image(image) {}

    int x()
    {
        return m_x;
    }
    
    int y()
    {
        return m_y;
    }

    int width()
    {
        return m_width;
    }

    int height()
    {
        return m_height;
    }

    bool CanMove()
    {
        return m_CanMove;
    }

    const QPixmap& image()
    {
        return m_image;
    }

    void setX(int x)
    {
        m_x = x;
    }

    void setY(int y)
    {
        m_y = y;
    }

    void setWIDTH(int width)
    {
        m_width = width;
    }

    void setHEIGHT(int heigth)
    {
        m_height = heigth;
    }

    void setCANMOVE(bool CanMove)
    {
        m_CanMove = CanMove;
    }

    void setImage(QPixmap& image)
    {
        m_image = image;
    }

};
