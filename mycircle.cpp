#include "mycircle.h"
#include <QPainter>

MyCircle::MyCircle():
    center(0, 0)
{
    radius = 0;
}

MyCircle::MyCircle(QPoint c, int radius):
    center(c)
{
    this->radius = radius;
}

MyCircle::MyCircle(int x, int y, int radius):
    center(x, y)
{
    this->radius = radius;
}

void MyCircle::translate(int x, int y)
{
    center.setX(center.x() + x);
    center.setY(center.y() + y);
}

void MyCircle::zoom(int p)
{
    if (p > 0)
    {
        radius = int(radius * (double(p) / 100));
    }
}

void MyCircle::rotate(int angle)
{
   ;
}

QPoint MyCircle::getFixedAnchor(QPoint p)
{
    QPoint p1(center.x() + radius, center.y() + radius);
    QPoint p2(center.x() + radius, center.y() - radius);
    QPoint p3(center.x() - radius, center.y() + radius);
    QPoint p4(center.x() - radius, center.y() - radius);
    int d1 = distance(p, p1);
    int d2 = distance(p, p2);
    int d3 = distance(p, p3);
    int d4 = distance(p, p4);
    if (d1 <= d2 && d1 <= d3 && d1 <= d4 && d1 <= 144)
    {
        return p4;
    }
    else if (d2 <= d1 && d2 <= d3 && d2 <= d4 && d2 <= 144)
    {
        return p3;
    }
    else if (d3 <= d1 && d3 <= d2 && d3 <= d4 && d3 <= 144)
    {
        return p2;
    }
    else if (d4 <= d1 && d4 <= d2 && d4 <= d3 && d4 <= 144)
    {
        return p1;
    }
    else
    {
        return QPoint(-1, -1);
    }
}

QPoint MyCircle::getSelectedAnchor(QPoint p)
{
    QPoint p1(center.x() + radius, center.y() + radius);
    QPoint p2(center.x() + radius, center.y() - radius);
    QPoint p3(center.x() - radius, center.y() + radius);
    QPoint p4(center.x() - radius, center.y() - radius);
    int d1 = distance(p, p1);
    int d2 = distance(p, p2);
    int d3 = distance(p, p3);
    int d4 = distance(p, p4);
    if (d1 <= d2 && d1 <= d3 && d1 <= d4 && d1 <= 144)
    {
        return p1;
    }
    else if (d2 <= d1 && d2 <= d3 && d2 <= d4 && d2 <= 144)
    {
        return p2;
    }
    else if (d3 <= d1 && d3 <= d2 && d3 <= d4 && d3 <= 144)
    {
        return p3;
    }
    else if (d4 <= d1 && d4 <= d2 && d4 <= d3 && d4 <= 144)
    {
        return p4;
    }
    else
    {
        return QPoint(-1, -1);
    }
}

void MyCircle::anchors(QImage *image)
{
    QPainter* painter = new QPainter(image);
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->drawRect(center.x() + radius, center.y() + radius, 5, 5);
    painter->drawRect(center.x() + radius, center.y() - radius, 5, 5);
    painter->drawRect(center.x() - radius, center.y() + radius, 5, 5);
    painter->drawRect(center.x() - radius, center.y() - radius, 5, 5);
    delete painter;
}

FUNCTION MyCircle::getShapeKind()
{
    return CIRCLE;
}

void MyCircle::draw(QImage* image, QColor* color)
{
    int x = 0;
    int y = radius;
    int p = 3 - 2 * radius;

    for ( ; x <= y; x++)
    {
        image->setPixelColor(x+center.x(), y+center.y(), *color);
        image->setPixelColor(-x+center.x(), y+center.y(), *color);
        image->setPixelColor(x+center.x(), -y+center.y(), *color);
        image->setPixelColor(-x+center.x(), -y+center.y(), *color);
        image->setPixelColor(y+center.x(), x+center.y(), *color);
        image->setPixelColor(-y+center.x(), x+center.y(), *color);
        image->setPixelColor(y+center.x(), -x+center.y(), *color);
        image->setPixelColor(-y+center.x(), -x+center.y(), *color);
        /*painter.drawPoint(x+center.x(), y+center.y());
        painter.drawPoint(-x+center.x(), y+center.y());
        painter.drawPoint(x+center.x(), -y+center.y());
        painter.drawPoint(-x+center.x(), -y+center.y());
        painter.drawPoint(y+center.x(), x+center.y());
        painter.drawPoint(-y+center.x(), x+center.y());
        painter.drawPoint(y+center.x(), -x+center.y());
        painter.drawPoint(-y+center.x(), -x+center.y());*/
        if (p >= 0)
        {
            p += 4 * (x - y) + 10;
            y--;
        }
        else
        {
            p += 4 * x + 6;
        }
    }
}
