#ifndef SEGMENT_H
#define SEGMENT_H
#include <QWidget>
#include <QFrame>

class segment : public QFrame
{
    int X1;
    int Y1;
    int X2;
    int Y2;
 public:
    segment(QWidget* parent = 0, int X1=0, int Y1=0, int X2=0, int Y2=0);
    int getX1();
    int getY1();
    int getX2();
    int getY2();
    void setPoint1(int X1, int Y1);
    void setPoint2(int X2, int Y2);

};

#endif // SEGMENT_H
