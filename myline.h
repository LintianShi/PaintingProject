#ifndef MYLINE_H
#define MYLINE_H
#include "myshape.h"
#include <QPoint>

class MyLine : public MyShape
{
private:
    QPoint begin;
    QPoint end;
public:
    MyLine();
    MyLine(int x0, int y0, int x1, int y1);
    MyLine(QPoint p0, QPoint p1);
    void draw(QImage* image, QColor* color);
    void translate(int x, int y);
    void zoom(int p);
    void rotate(int angle);
    void anchors(QImage* image);
    FUNCTION getShapeKind();
    QPoint getFixedAnchor(QPoint p);
    QPoint getSelectedAnchor(QPoint p);
    QPoint getBegin();
    QPoint getEnd();
    //bool isSelectedAnchor();
};

#endif // MYLINE_H
