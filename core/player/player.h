#pragma once
#include <string>

class Player
{
   private:
    std::string m_name;
    int m_x;
    int m_y;

   public:
    std::string name()
    {
        return m_name;
    }

    int x()
    {
        return m_x;
    }

    int y()
    {
        return m_y;
    }

    void setNAME(std::string name)
    {
        m_name = name;
    }

    void setX(int x)
    {
        m_x = x;
    }

    void setY(int y)
    {
        m_y = y;
    }

};
