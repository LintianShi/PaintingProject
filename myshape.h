#ifndef MYSHAPE_H
#define MYSHAPE_H
#include <QImage>
#include "function.h"
#include <cmath>

class MyShape
{
public:
    virtual void draw(QImage* image, QColor* color);
    virtual void translate(int x, int y);
    virtual void zoom(int p);
    virtual void rotate(int angle);
    virtual void anchors(QImage* image);
    virtual FUNCTION getShapeKind();
    virtual QPoint getFixedAnchor(QPoint p);
    virtual QPoint getSelectedAnchor(QPoint p);
    int distance(QPoint p1, QPoint p2);
};

#endif // MYSHAPE_H
