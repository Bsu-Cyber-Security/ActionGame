#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Game;
}
QT_END_NAMESPACE

class Game : public QMainWindow {
    Q_OBJECT

   public:
    explicit Game(QWidget *parent = nullptr);
    virtual ~Game();

   private:
    Ui::Game *ui;
};
