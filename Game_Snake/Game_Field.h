#ifndef GAME_FIELD_H
#define GAME_FIELD_H
#include <QFrame>
#include <QWidget>
#include "Snake.h"
#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTime>
#include <QList>

enum game_status
{
    wait = 0,
    play = 1,
    snake_death = 2,
    gameover = 3,
    success = 4
};

class Game_Field : public QFrame
{
    Q_OBJECT
private:
    //служебные параметры класса
    int step;
    int field_X;
    int field_Y;
    int default_snake_size;
    int default_snake_X;
    int default_snake_Y;
    int death_time;

    //информационные параметры игры
    int level;
    int lifes;
    int points;
    int target_points;

    game_status game_stat=wait;

    QFrame* apple;          //яблоко
    Snake* snake;           //змейка
    QVector<QFrame*> barriers;  //препятствия на поле
    QTimer* game_timer;     //игровой таймер
    QTimer* death_timer;     //таймер смерти змейки
    QSound* eat_sound;
    QSound* death_sound;
    QMediaPlayer* music;
    QList<int> test_list;

  //Конструкторы
public:
    Game_Field(QWidget* parent, int new_field_X, int new_field_Y, int step);

    //Методы

    //Интерфейсные методы для взаимодействия с объектом
    int getLifes();
    int getLevel();
    int getDefaultSnakeSize();
    int getPoints();
    int getTargetPoints();
    game_status getGameStatus();
    bool setLifes(int new_lives);
    bool setLevel(int new_level);
    bool setDefaultSnakeSize(int new_snake_size);
    bool setPoints(int new_points);
    bool setTargetPoints(int new_target_points);
    bool setAllGameParameters(int new_points,int new_target_points, int new_lifes, int new_level);
    //служебные методы
private:
    void keyPressEvent(QKeyEvent* key_event);
    bool checkBarrierIntersection(QFrame* object);
    bool checkBarrierIntersection(QRect object);
    void death();
public:
    //Деструктор
    ~Game_Field();

signals:
    void death_signal();
    void gameover_signal();
    void refresh_signal();
    void success_signal();
    void fault_signal();
public slots:
    //Сигналы и слоты
    void gameCycle();               //главный цикл игры
    void startGame();               //команда запуска игры
    void stopGame();                //команда останова игры
    void resetGame();
    void deathCycle();              //цикл смерти змейки

    //Слоты музыки
    void startMusic();
    void stopMusic();


};

#endif // GAME_FIELD_H
