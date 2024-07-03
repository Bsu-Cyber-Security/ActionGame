#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QTextStream>
#include <QGraphicsSimpleTextItem>
#include <QPoint>
#include <QDir>
#include <QPushButton>
#include <cmath>
#include <map>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include <algorithm>
#include "app/scene/gamescene.h"
GameScene::GameScene(QObject *parent): QGraphicsScene(parent), numberOfPlayers(2)
{
    // Создаем новое окно для кнопки
    QWidget* buttonWindow = new QWidget();
    buttonWindow->setWindowTitle("Кнопка");
    buttonWindow->setFixedSize(200, 200);

            // Создаем кнопку и добавляем ее в правый нижний угол окна
    QPushButton* button = new QPushButton("Клик");
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addStretch();
    layout->addWidget(button);
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addStretch();
    mainLayout->addLayout(layout);
    buttonWindow->setLayout(mainLayout);

    //connect(button, &QPushButton::clicked, this, &GameScene::showDiceAnimation);
    buttonWindow->show(); // Показываем окно с кнопкой


            // Остальной код конструктора GameScene
    setSceneRect(0, 0, 800, 800);
    readLevelsFile("C:/Users/vtali/Documents/ActionGame/Resource/map.txt");
    drawMap();
    runLevel();

}


std::vector<std::vector<int>> map(20, std::vector<int>(20));
std::map<int, QPixmap> playerImages;
std::vector<QPoint> coordination(37);

// void GameScene::showDiceAnimation(int result) {

//     QString gifPath;
//     switch (result) {
//         case 1:
//             gifPath = "D:/Qt/ActionGame/Resource/1dis.gif";
//             break;
//         case 2:
//             gifPath ="D:/Qt/ActionGame/Resource/2dis.gif" ;
//             break;
//         case 3:
//             gifPath = "D:/Qt/ActionGame/Resource/3dis.gif";
//             break;
//         case 4:
//             gifPath = "D:/Qt/ActionGame/Resource/4dis.gif";
//             break;
//         case 5:
//             gifPath = "D:/Qt/ActionGame/Resource/5dis.gif" ;
//             break;
//         case 6:
//             gifPath = "D:/Qt/ActionGame/Resource/6dis.gif";
//             break;
//     }


//     QWidget* animationWindow = new QWidget();
//     animationWindow->setWindowTitle("Анимация костей");
//     animationWindow->setFixedSize(300, 450);


//     QLabel* diceLabel = new QLabel(animationWindow);
//     diceLabel->setAlignment(Qt::AlignCenter);


//     QMovie* movie = new QMovie(gifPath);
//     diceLabel->setMovie(movie);

//     QVBoxLayout* layout = new QVBoxLayout(animationWindow);
//     layout->addWidget(diceLabel);
//     animationWindow->setLayout(layout);
//     movie->start();
//     animationWindow->show();
// }

void GameScene::readLevelsFile(QString pathFile) {
    QFile file(pathFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);// Initialize with -1 for walls

        int row = 0;
        while (!in.atEnd() && row < 20) { // Limit to 20 rows
            QString line = in.readLine();
            if (!line.isEmpty()) {
                QStringList elements = line.split(" "); // Split by spaces

                for (int col = 0; col < elements.size() && col < 20; ++col) {
                    int value = elements[col].toInt();
                    map[row][col] = value;
                }
                row++;
            }
        }
        file.close();


        // For debugging
        std::cout << "Map Contents:\n";
        for (int row = 0; row < 20; ++row) {
            for (int col = 0; col < 20; ++col) {
                std::cout << map[row][col] << " ";
            }
            std::cout << std::endl;
        }
        for (int row = 0; row < 20; ++row) {
            for (int col = 0; col < 20; ++col) {
                if (map[row][col] != -1){
                    QPoint c;
                    c.setX(40*(col));
                    c.setY(40*(row));
                    coordination[map[row][col]] = c;
                }
            }
        }
    } else {
        std::cerr << "Failed to open file: " << pathFile.toStdString() << std::endl;
    }

}

bool GameScene::CompareCoord(int c){
    if(c >= 37){
        return true;
    }
    return false;
}


void GameScene::runLevel() {
    std::vector<int> position(numberOfPlayers, 0);
    QMessageBox* victory_window = new QMessageBox();
    int winningPlayerIndex;

    initializePlayerImages();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    while (gameIsActive) {
        for (int playerIndex = 0; playerIndex < numberOfPlayers; ++playerIndex) {
            int roll = std::rand() % 6 + 1;
            position[playerIndex] += roll;
            redrawPlayers(position, playerIndex);
            if (CompareCoord(position[playerIndex])) {
                gameIsActive = false; // Завершаем игру
                winningPlayerIndex = playerIndex;
                break; // Выходим из цикла
            }
        }
    }

    QString message = "Игрок " + QString::number(winningPlayerIndex + 1) + " победил!";
    victory_window->setText(message);
    victory_window->setWindowTitle("Победа!");

    QPushButton* playAgainButton = victory_window->addButton(tr("Играть заново"), QMessageBox::AcceptRole);
    QPushButton* closeButton = victory_window->addButton(tr("Закрыть приложение"), QMessageBox::RejectRole);

    QObject::connect(playAgainButton, &QPushButton::clicked, [=]() {
        runLevel();
    });

    QObject::connect(closeButton, &QPushButton::clicked, [=]() {
        QApplication::quit();
    });

    victory_window->exec();
}
void GameScene::drawMap(){
    QPixmap background ("C:/Users/vtali/Documents/ActionGame/Resource/2.jpg");
    // Создаем элемент для фона и устанавливаем его размер равным размеру сцены
    QGraphicsPixmapItem* backgroundItem = addPixmap(background.scaled(width(), height()));



    QPixmap road("C:/Users/vtali/Documents/ActionGame/Resource/road.jpg"); // Путь к изображению дорожки
    int tileSize = 40; // Размер одной плитки

            // Проходим по матрице карты и рисуем дорожки
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] != -1 ) {
                QGraphicsPixmapItem* roadItem = new QGraphicsPixmapItem(road);
                // Устанавливаем размер плитки дорожки
                roadItem->setPixmap(road.scaled(tileSize, tileSize));
                // Устанавливаем позицию элемента дорожки
                roadItem->setPos( j * tileSize, i * tileSize);
                // Добавляем элемент дорожки в сцену
                addItem(roadItem);
            }
        }
    }
}

void GameScene::initializePlayerImages()
{
    // Инициализация изображений игроков
    playerImages[0] = QPixmap("C:/Users/vtali/Documents/ActionGame/Resource/cloud.png");
    playerImages[1] = QPixmap("C:/Users/vtali/Documents/ActionGame/Resource/ball.png");
    QPixmap playerPixmap0 = playerImages[0];
    // Масштабируем картинку до заданного размера
    playerPixmap0 = playerPixmap0.scaled(40, 40, Qt::KeepAspectRatio);
    // Создаем графический элемент для картинки игрока
    QGraphicsPixmapItem* playerItem0 = new QGraphicsPixmapItem(playerPixmap0);
    playerItem0->setPos(coordination[0]);
    this->addItem(playerItem0);
    QPixmap playerPixmap1 = playerImages[1];
    // Масштабируем картинку до заданного размера
    playerPixmap1 = playerPixmap1.scaled(40, 40, Qt::KeepAspectRatio);
    // Создаем графический элемент для картинки игрока
    QGraphicsPixmapItem* playerItem1 = new QGraphicsPixmapItem(playerPixmap1);
    playerItem1->setPos(coordination[0]);
    this->addItem(playerItem1);

}

std::vector<QGraphicsPixmapItem*> playerGraphicsItems;

void GameScene::redrawPlayers(std::vector<int>& m, int player_index) {
    // Получаем количество игроков
    const int numPlayers = m.size();
    // Определяем размер картинок игроков
    int playerImageSize = 40;

            // Если это первый ход, нужно инициализировать вектор графических элементов
    if (playerGraphicsItems.empty()) {
        playerGraphicsItems.resize(numPlayers, nullptr);
    }

    // Если у игрока уже есть графический элемент, удаляем его
    if (playerGraphicsItems[player_index] != nullptr) {
        this->removeItem(playerGraphicsItems[player_index]);
        delete playerGraphicsItems[player_index];
        playerGraphicsItems[player_index] = nullptr;
    }

            // Получаем изображение для текущего игрока из мапы
    QPixmap playerPixmap = playerImages[player_index];
    // Масштабируем картинку до заданного размера
    playerPixmap = playerPixmap.scaled(playerImageSize, playerImageSize, Qt::KeepAspectRatio);

            // Создаем новый графический элемент для картинки игрока
    QGraphicsPixmapItem* playerItem = new QGraphicsPixmapItem(playerPixmap);
    // Устанавливаем позицию игрока на поле, используя координаты из вектора coordination
    playerItem->setPos(coordination[m[player_index]].x(), coordination[m[player_index]].y());
    // Добавляем игрока на сцену
    this->addItem(playerItem);

            // Сохраняем указатель на новый элемент
    playerGraphicsItems[player_index] = playerItem;
}
