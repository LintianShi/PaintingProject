#include "myshape.h"
int MyShape::distance(QPoint p1, QPoint p2)
{
    return (abs(p1.x() - p2.x())) * (abs(p1.x() - p2.x())) + (abs(p1.y() - p2.y())) * (abs(p1.y() - p2.y()));
}

QPoint MyShape::getFixedAnchor(QPoint p)
{
    return QPoint(-1, -1);
}
QPoint MyShape::getSelectedAnchor(QPoint p)
{
    return QPoint(-1, -1);
}
