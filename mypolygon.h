#ifndef MYPOLYGON_H
#define MYPOLYGON_H
#include <vector>
#include <QPoint>
#include "myshape.h"
using namespace std;



class MyPolygon : public MyShape
{
private:
    vector<QPoint> vertex;
    QPoint getMidPoint();
public:
    //MyPolygon();
    MyPolygon(vector<QPoint> p);
    void draw(QImage* image, QColor* color);
    void translate(int x, int y);
    void zoom(int p);
    void rotate(int angle);
    void anchors(QImage* image);
    void drawTemp(QImage* image, QColor* color);
    void change(QPoint before, QPoint after);
    QPoint getFixedAnchor(QPoint p);
    QPoint getSelectedAnchor(QPoint p);
    FUNCTION getShapeKind();
};

#endif // MYPOLYGON_H
