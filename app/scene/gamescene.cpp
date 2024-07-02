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
#include <QHBoxLayout>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QRandomGenerator>

#include "app/scene/game_state.h"
#include "app/scene/gamescene.h"
#include "app/pixmap_manager/pixmap_manager.h"

int count = 0;


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


            // Подключаем сигнал нажатия кнопки к слоту Click()
    connect(button, &QPushButton::clicked, this, &GameScene::showDiceAnimation);

    buttonWindow->show(); // Показываем окно с кнопкой


            // Остальной код конструктора GameScene
    setSceneRect(0, 0, 800, 800);
    readLevelsFile("C:/Users/nikit/ActionGame/Resource/map.txt");
    drawMap();
    runLevel();
}


std::vector<std::vector<char>> map(20, std::vector<char>(20));
std::vector<QPoint> path;
std::map<int, QPixmap> playerImages;


void GameScene::showDiceAnimation() {

    int result = QRandomGenerator::global()->generate() % 6 + 1;


    QString gifPath;
    switch (result) {
        case 1:
            gifPath = "C:/Users/nikit/ActionGame/Resource/1dis.gif";
            break;
        case 2:
            gifPath = "C:/Users/nikit/ActionGame/Resource/2dis.gif";
            break;
        case 3:
            gifPath = "C:/Users/nikit/ActionGame/Resource/3dis.gif";
            break;
        case 4:
            gifPath = "C:/Users/nikit/ActionGame/Resource/4dis.gif";
            break;
        case 5:
            gifPath = "C:/Users/nikit/ActionGame/Resource/5dis.gif";
            break;
        case 6:
            gifPath = "C:/Users/nikit/ActionGame/Resource/6dis.gif";
            break;
    }


    QWidget* animationWindow = new QWidget();
    animationWindow->setWindowTitle("Анимация костей");
    animationWindow->setFixedSize(300, 450);


    QLabel* diceLabel = new QLabel(animationWindow);
    diceLabel->setAlignment(Qt::AlignCenter);


    QMovie* movie = new QMovie(gifPath);
    diceLabel->setMovie(movie);

    QVBoxLayout* layout = new QVBoxLayout(animationWindow);
    layout->addWidget(diceLabel);
    animationWindow->setLayout(layout);

    movie->start();



    QTimer* timer = new QTimer(animationWindow);
    QObject::connect(timer, &QTimer::timeout, [movie]() {
        movie->stop();
    });
    switch (result)
    {
        case 1:
            timer->start(3120);
            break;
        case 2:
            timer->start(4320);
            break;
        case 3:
            timer->start(3220);
            break;
        case 4:
            timer->start(4420);
            break;
        case 5:
            timer->start(4420);
            break;
        case 6:
            timer->start(3220);
            break;
        default:
            break;
    }


    animationWindow->show();
}

void GameScene::Click(){

    QPixmap playerPixmap = playerImages[1];
    // Масштабируем картинку до заданного размера
    playerPixmap = playerPixmap.scaled(40,40, Qt::KeepAspectRatio);
    // Создаем графический элемент для картинки игрока
    QGraphicsPixmapItem* playerItem = new QGraphicsPixmapItem(playerPixmap);
    // Устанавливаем позицию графического элемента
    playerItem->setPos(path[count].x(),path[count].y());
    // Устанавливаем выравнивание по верхнему краю
    // Добавляем графический элемент на сцену
    this->addItem(playerItem);
    count+=1;
}
void GameScene::readLevelsFile(QString pathFile)
{
    QFile file(pathFile);

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);

        for (int i = 0; i < 20; ++i)
        {
            QString line = in.readLine();
            QStringList cells = line.split(' ');

            if (cells.size() == 20)
            {
                for (int j = 0; j < 20; ++j)
                {
                    map[i][j] = cells[j].toLatin1()[0];
                    if(map[i][j] == '3'){
                        this->endCoord.setX(i);
                        this->endCoord.setY(j);
                    }
                    else if(map[i][j == '2']){
                        this->startCoord.setX(i);
                        this->startCoord.setY(j);
                    }
                }

            }

            else
            {
                qDebug() << "Error: Invalid map data in line" << i + 1;
            }
        }
        file.close();
    }
    else
    {
        qDebug() << "Error: Failed to open file" << pathFile;
    }
}

void GameScene::runLevel(){
    std::vector<std::pair<QPoint, QString>> m_players(this->numberOfPlayers);

    //Инциализация игроков
    for(auto player : m_players)  {
        player.first = startCoord;
    }
    //Игровой цикл
    initializePlayerImages();
    drawPlayers(m_players);

    while(gameIsActive)
    {
        for(int playerIndex = 0; playerIndex < numberOfPlayers; ++playerIndex)
        {
            std::srand(time(0));
            int roll = std::rand()%6 + 1;

            if(m_players[playerIndex].first == this->endCoord)
            {
                gameIsActive = false; // Завершаем игру
                break; // Выходим из цикла
            }
            else
            {
                //updatePlayerStatus(playerIndex); // Обновляем статус текущего игрока
                //drawBoard(playerIndex); // Перерисовываем доску для текущего игрока
            }

                //resetStatus(playerIndex); // Сбрасываем статус для следующего обновления цикла
        }
    }
}

void GameScene::drawMap(){
    QPixmap background ("C:/Users/nikit/ActionGame/Resource/2.jpg");
    // Создаем элемент для фона и устанавливаем его размер равным размеру сцены
    QGraphicsPixmapItem* backgroundItem = addPixmap(background.scaled(width(), height()));



    QPixmap road("C:/Users/nikit/ActionGame/Resource/road.jpg"); // Путь к изображению дорожки
    int tileSize = 40; // Размер одной плитки

            // Проходим по матрице карты и рисуем дорожки
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] != '0') {
                QGraphicsPixmapItem* roadItem = new QGraphicsPixmapItem(road);
                // Устанавливаем размер плитки дорожки
                roadItem->setPixmap(road.scaled(tileSize, tileSize));
                // Устанавливаем позицию элемента дорожки
                roadItem->setPos(j * tileSize, i * tileSize);
                // Добавляем элемент дорожки в сцену
                addItem(roadItem);
            }
        }
    }
}

void GameScene::initializePlayerImages() {
    // Инициализация изображений игроков
    playerImages[0] = QPixmap("C:/Users/nikit/ActionGame/Resource/ball.png");
    playerImages[1] = QPixmap("C:/Users/nikit/ActionGame/Resource/cloud.png");
}

void GameScene::drawPlayers(std::vector<std::pair<QPoint, QString>>& m_players) {
    // Получаем размер клетки
    const int cellSize = 40; // Пример размера клетки
    // Получаем количество игроков
    const int numPlayers = m_players.size();
    // Определяем размер картинок игроков
    int playerImageSize = 40;
    // Перебираем всех игроков
    for (size_t i = 0; i < numPlayers; ++i) {
        QPixmap playerPixmap = playerImages[i];
        // Масштабируем картинку до заданного размера
        playerPixmap = playerPixmap.scaled(playerImageSize, playerImageSize, Qt::KeepAspectRatio);
        // Создаем графический элемент для картинки игрока
        QGraphicsPixmapItem* playerItem = new QGraphicsPixmapItem(playerPixmap);
        // Вычисляем координаты для размещения картинки
        int x = startCoord.x() + i*playerImageSize;
        int y = startCoord.y();
        // Устанавливаем позицию графического элемента
        playerItem->setPos(360, 320);
        // Устанавливаем выравнивание по верхнему краю
        // Добавляем графический элемент на сцену
        this->addItem(playerItem);
    }
}
