#ifndef MYCURVE_H
#define MYCURVE_H
#include "myshape.h"
#include <vector>
using namespace std;

class MyCurve : public MyShape
{
private:
    vector<QPoint> jd;
    int np;
    double tension;
    int grain;
    double mc[16];
    double getMatrix(double p0, double p1, double p2, double p3, double u);
    QPoint getMidPoint();
public:
    MyCurve();
    MyCurve(vector<QPoint> points);
    void draw(QImage* image, QColor* color);
    void translate(int x, int y);
    void zoom(int p);
    void rotate(int angle);
    void anchors(QImage* image);
    QPoint getFixedAnchor(QPoint p);
    QPoint getSelectedAnchor(QPoint p);
    void change(QPoint before, QPoint after);
    FUNCTION getShapeKind();
};

#endif // MYCURVE_H
