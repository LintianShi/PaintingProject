#ifndef MYOVAL_H
#define MYOVAL_H
#include "myshape.h"

class MyOval : public MyShape
{
private:
    QPoint center;
    int a;
    int b;
public:
    MyOval();
    MyOval(QPoint c, int a, int b);
    MyOval(int x, int y, int a, int b);
    void draw(QImage* image, QColor* color);
    void translate(int x, int y);
    void zoom(int p);
    void rotate(int angle);
    void anchors(QImage* image);
    FUNCTION getShapeKind();
    QPoint getFixedAnchor(QPoint p);
    QPoint getSelectedAnchor(QPoint p);
    static int angle;
};

#endif // MYOVAL_H
