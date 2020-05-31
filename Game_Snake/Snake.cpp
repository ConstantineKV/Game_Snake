#include "Snake.h"
#include <QFrame>
#include <QVector>
#include <vector>

Snake::Snake(QWidget* parent) : QWidget(parent), step(10)
{
    stretch = 10;
    QFrame* part = new QFrame(this);


    part = new QFrame(this);
    part->setFrameShape(QFrame::Box);
    part->setLineWidth(step);
    part->setGeometry(0+step,0,step,step);
    parts.push_back(part);
    part = new QFrame(this);
    part->setFrameShape(QFrame::Box);
    part->setLineWidth(step);
    part->setGeometry(0+step*2,0,step,step);
    parts.push_back(part);
    direction = s_right;
    number_of_parts = 3;
}

Snake::Snake(QWidget* parent,int stretch) : QWidget(parent), step(10)
{
    QFrame* part;

    for(int i=0;i<stretch;i++)
    {
        part = new QFrame(this);
        part->setFrameShape(QFrame::Box);
        part->setLineWidth(step);
        part->setGeometry(0+step*i,0,step,step);
        parts.push_back(part);

    }
    direction = s_right;
    number_of_parts = stretch;
}

Snake::Snake(QWidget* parent,int stretch, int start_X, int start_Y, int new_step) : QWidget(parent)
{
    QFrame* part;
    step = new_step;
    for(int i=0;i<stretch;i++)
    {
        part = new QFrame(this);
        part->setFrameShape(QFrame::Box);
        part->setLineWidth(step);
        part->setGeometry(start_X+step*i,start_Y,step,step);
        parts.push_back(part);

    }
    direction = s_right;
    number_of_parts = stretch;
}

Snake::Snake() : step(10)
{
    QFrame* part = new QFrame(this);

    part->setFrameShape(QFrame::Box);
    part->setLineWidth(step);

    part->setGeometry(0,0,step,step);
    parts.push_back(part);
    part = new QFrame(this);
    part->setFrameShape(QFrame::Box);
    part->setLineWidth(step);
    part->setGeometry(0+step,0,step,step);
    parts.push_back(part);
    part = new QFrame(this);
    part->setFrameShape(QFrame::Box);
    part->setLineWidth(step);
    part->setGeometry(0+step*2,0,step,step);
    parts.push_back(part);
    direction = s_right;
    number_of_parts = 3;
}



void Snake::Move()//Функция движения змейки
{
QFrame* part;
QRect rect_temp;
    switch(direction)
    {
       case s_up:
            part = new QFrame(this);
            part->show();
            part->setFrameShape(QFrame::Box);
            rect_temp = parts[parts.size()-1]->geometry();
            part->setLineWidth(step);
            rect_temp.setTop(rect_temp.top() - step);
            rect_temp.setBottom(rect_temp.bottom() - step);
            part->setGeometry(rect_temp);
            last_direction = s_up;
            parts.push_back(part);
            delete parts[0];
            parts.erase(parts.begin());
            break;
       case s_down:
            part = new QFrame(this);
            part->show();
            part->setFrameShape(QFrame::Box);
            rect_temp = parts[parts.size()-1]->geometry();
            part->setLineWidth(step);
            rect_temp.setTop(rect_temp.top() + step);
            rect_temp.setBottom(rect_temp.bottom() + step);
            part->setGeometry(rect_temp);
            last_direction = s_down;
            parts.push_back(part);
            delete parts[0];
            parts.erase(parts.begin());
            break;
       case s_left:
            part = new QFrame(this);
            part->show();
            part->setFrameShape(QFrame::Box);
            rect_temp = parts[parts.size()-1]->geometry();
            part->setLineWidth(step);
            rect_temp.setLeft(rect_temp.left() - step);
            rect_temp.setRight(rect_temp.right() - step);
            part->setGeometry(rect_temp);
            last_direction = s_left;
            parts.push_back(part);
            delete parts[0];
            parts.erase(parts.begin());
            break;
       case s_right:
            part = new QFrame(this);
            part->show();
            part->setFrameShape(QFrame::Box);
            rect_temp = parts[parts.size()-1]->geometry();
            part->setLineWidth(step);
            rect_temp.setLeft(rect_temp.left() + step);
            rect_temp.setRight(rect_temp.right() + step);
            part->setGeometry(rect_temp);
            last_direction = s_right;
            parts.push_back(part);
            delete parts[0];
            parts.erase(parts.begin());
            break;
      default:
            break;

       }

}


void Snake::Rise()
{
    QFrame* part;
    QRect rect_temp;
        switch(direction)
        {
           case s_up:
                part = new QFrame(this);
                part->show();
                part->setFrameShape(QFrame::Box);
                rect_temp = parts[parts.size()-1]->geometry();
                part->setLineWidth(step);
                rect_temp.setTop(rect_temp.top() - step);
                rect_temp.setBottom(rect_temp.bottom() - step);
                part->setGeometry(rect_temp);
                parts.push_back(part);
                last_direction = s_up;
                break;
           case s_down:
                part = new QFrame(this);
                part->show();
                part->setFrameShape(QFrame::Box);
                rect_temp = parts[parts.size()-1]->geometry();
                part->setLineWidth(step);
                rect_temp.setTop(rect_temp.top() + step);
                rect_temp.setBottom(rect_temp.bottom() + step);
                part->setGeometry(rect_temp);
                parts.push_back(part);
                last_direction = s_down;
                break;
           case s_left:
                part = new QFrame(this);
                part->show();
                part->setFrameShape(QFrame::Box);
                rect_temp = parts[parts.size()-1]->geometry();
                part->setLineWidth(step);
                rect_temp.setLeft(rect_temp.left() - step);
                rect_temp.setRight(rect_temp.right() - step);
                part->setGeometry(rect_temp);
                parts.push_back(part);
                last_direction = s_left;
                break;
           case s_right:
                part = new QFrame(this);
                part->show();
                part->setFrameShape(QFrame::Box);
                rect_temp = parts[parts.size()-1]->geometry();
                part->setLineWidth(step);
                rect_temp.setLeft(rect_temp.left() + step);
                rect_temp.setRight(rect_temp.right() + step);
                part->setGeometry(rect_temp);
                parts.push_back(part);
                last_direction = s_right;
                break;
          default:
                break;

           }

}

void Snake::setDirection(dir new_direction)
{
    if((new_direction == s_up) && (last_direction == s_down))
        return;
    if((new_direction == s_down) && (last_direction == s_up))
        return;
    if((new_direction == s_left) && (last_direction == s_right))
        return;
    if((new_direction == s_right) && (last_direction == s_left))
        return;
    direction = new_direction;
}

bool Snake::checkAppleIntersection(QFrame* apple)
{
    QRect rect_temp_snake, rect_apple_temp;
    rect_apple_temp = apple->geometry();

    for(QVector<QFrame*>::iterator iter=parts.begin(); iter!=parts.end();iter++)
    {
        QFrame* frame_temp = *iter;
        QRect rect_inter;
        rect_temp_snake = frame_temp->geometry();
        rect_inter = rect_temp_snake&rect_apple_temp;
        if(rect_inter.isNull())
            continue;
        else
            return true;
    }
    return false;

}

QRect Snake::getNextPosition()
{
    QRect rect_temp;
        switch(direction)
        {
           case s_up:

                rect_temp = parts[parts.size()-1]->geometry();
                rect_temp.setTop(rect_temp.top() - step);
                rect_temp.setBottom(rect_temp.bottom() - step);
                return rect_temp;
                break;
           case s_down:
                rect_temp = parts[parts.size()-1]->geometry();
                rect_temp.setTop(rect_temp.top() + step);
                rect_temp.setBottom(rect_temp.bottom() + step);
                return rect_temp;
                break;
           case s_left:
                rect_temp = parts[parts.size()-1]->geometry();
                rect_temp.setLeft(rect_temp.left() - step);
                rect_temp.setRight(rect_temp.right() - step);
                break;
           case s_right:
                rect_temp = parts[parts.size()-1]->geometry();
                rect_temp.setLeft(rect_temp.left() + step);
                rect_temp.setRight(rect_temp.right() + step);
                break;
          default:
                return rect_temp;
                break;

           }
}

bool Snake::isMoveAcross()
{
    QRect next_pos = getNextPosition();
    QRect rect_temp_snake;

    for(QVector<QFrame*>::iterator iter=parts.begin(); iter!=parts.end();iter++)
    {
        QFrame* frame_temp = *iter;
        QRect rect_inter;
        rect_temp_snake = frame_temp->geometry();
        rect_inter = rect_temp_snake&next_pos;

        if(rect_inter.isNull())
            continue;
        else
            return true;
    }
    return false;
}
//Деструктор
Snake::~Snake()
{
    for(int i=0;i<parts.size();i++)
    {
        delete parts[i];
    }
    parts.clear();
}
