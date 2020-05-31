#ifndef SNAKE_H
#define SNAKE_H
#include <QWidget>
#include <QFrame>
#include <QLine>
#include <QVector>

enum dir
{
    s_up = 1,
    s_down = 2,
    s_left = 3,
    s_right = 4

};

class Snake : public QWidget
{
    Q_OBJECT

    //Параметры
    int step;                           //количество пикселей граней сегментов змейки
    int stretch;                        //длина змейки
    dir direction;                      //направление, куда змейка намерена сходить
    dir last_direction;                 //направление, куда змейка сходила последний раз
    int number_of_parts;

    QVector<QFrame*> parts;             //сегменты змейки


    //Конструкторы
  public:
    explicit Snake(QWidget* parent = 0);
    explicit Snake(QWidget* parent, int stretch);
    explicit Snake(QWidget* parent, int stretch, int start_X, int start_Y, int new_step);
    explicit Snake();

    //Деструктор
    ~Snake();
    //Методы
    bool checkAppleIntersection(QFrame* apple);      //Возвращает true, если голова змейки попала на яблоко
    QRect getNextPosition();                         //Возвращает коориднаты следующей позиции змейки
    bool isMoveAcross();                             //Возвращает true, если змейка движется через свой хвост
  public slots:
    void Move();
    void Rise();
    void setDirection(dir new_direction);

};

#endif // SNAKE_H
