#ifndef MYCIRCLE_H
#define MYCIRCLE_H
#include "myshape.h"
#include <QPoint>

class MyCircle : public MyShape
{
private:
    QPoint center;
    int radius;
public:
    MyCircle();
    MyCircle(QPoint c, int radius);
    MyCircle(int x, int y, int radius);
    void draw(QImage* image, QColor* color);
    void translate(int x, int y);
    void zoom(int p);
    void rotate(int angle);
    void anchors(QImage* image);
    FUNCTION getShapeKind();
    QPoint getFixedAnchor(QPoint p);
    QPoint getSelectedAnchor(QPoint p);
};

#endif // MYCIRCLE_H
