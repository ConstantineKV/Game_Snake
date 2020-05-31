#include "segment.h"

segment::segment(QWidget* parent,int new_X1, int new_Y1, int new_X2, int new_Y2) : QFrame(parent)
{
    X1 = new_X1;
    Y1 = new_Y1;
    X2 = new_X2;
    Y2 = new_Y2;

}

int segment::getX1()
{
    return X1;
}

int segment::getY1()
{
    return Y1;
}

int segment::getX2()
{
    return X2;
}

int segment::getY2()
{
    return Y2;
}

void segment::setPoint1(int X1, int Y1)
{
    QRect rect_temp;
    rect_temp = this->geometry();


}
