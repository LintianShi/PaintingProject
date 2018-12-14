#include "myoval.h"
#include <QPainter>
MyOval::MyOval():
    center(0, 0)
{
    a = 0;
    b = 0;
    //MyOval::angle = 0;
}

MyOval::MyOval(int x, int y, int a, int b):
    center(x, y)
{
    this->a = a;
    this->b = b;
    //MyOval::angle = 0;
}

MyOval::MyOval(QPoint c, int a, int b):
    center(c)
{
    this->a = a;
    this->b = b;
    //MyOval::angle = 0;
}

void MyOval::translate(int x, int y)
{
    center.setX(center.x() + x);
    center.setY(center.y() + y);
}

void MyOval::zoom(int p)
{
    if (p > 0)
    {
        a = int(a * (double(p) / 100));
        b = int(b * (double(p) / 100));
    }
}

void MyOval::rotate(int angle)
{
    MyOval::angle += angle;
}

void MyOval::anchors(QImage *image)
{
    QPainter* painter = new QPainter(image);
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->drawRect(center.x() + a, center.y() + b, 5, 5);
    painter->drawRect(center.x() + a, center.y() - b, 5, 5);
    painter->drawRect(center.x() - a, center.y() + b, 5, 5);
    painter->drawRect(center.x() - a, center.y() - b, 5, 5);
    //painter->drawRect(end.x(), end.y(), 5, 5);
    delete painter;
}

QPoint MyOval::getFixedAnchor(QPoint p)
{
    QPoint p1(center.x() + a, center.y() + b);
    QPoint p2(center.x() + a, center.y() - b);
    QPoint p3(center.x() - a, center.y() + b);
    QPoint p4(center.x() - a, center.y() - b);
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

QPoint MyOval::getSelectedAnchor(QPoint p)
{

    QPoint p1(center.x() + a, center.y() + b);
    QPoint p2(center.x() + a, center.y() - b);
    QPoint p3(center.x() - a, center.y() + b);
    QPoint p4(center.x() - a, center.y() - b);
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

FUNCTION MyOval::getShapeKind()
{
    return OVAL;
}

void MyOval::draw(QImage *image, QColor *color)
{
    double c = cos(double(MyOval::angle) * 3.14159265358 / 180);
    double s = sin(double(MyOval::angle) * 3.14159265358 / 180);
    int x = 0;
    int y = b;
    int p = b * b - a * a * b + a * a / 4;
    while (b * b * x < a * a * y)
    {
        image->setPixelColor(int(x * c - y * s) + center.x(), int(x * s + y * c) + center.y(), *color);
        image->setPixelColor(int(-x * c - y * s) + center.x(), int(-x * s + y * c) + center.y(), *color);
        image->setPixelColor(int(x * c + y * s) + center.x(), int(x * s - y * c) + center.y(), *color);
        image->setPixelColor(int(-x * c + y * s) + center.x(), int(-x * s - y * c) + center.y(), *color);
        image->setPixelColor(int(x * c - y * s)+1 + center.x(), int(x * s + y * c) + center.y(), *color);
        image->setPixelColor(int(-x * c - y * s)+1 + center.x(), int(-x * s + y * c) + center.y(), *color);
        image->setPixelColor(int(x * c + y * s)+1 + center.x(), int(x * s - y * c) + center.y(), *color);
        image->setPixelColor(int(-x * c + y * s)+1 + center.x(), int(-x * s - y * c) + center.y(), *color);
        image->setPixelColor(int(x * c - y * s) + center.x(), int(x * s + y * c)+1 + center.y(), *color);
        image->setPixelColor(int(-x * c - y * s) + center.x(), int(-x * s + y * c)+1 + center.y(), *color);
        image->setPixelColor(int(x * c + y * s) + center.x(), int(x * s - y * c)+1 + center.y(), *color);
        image->setPixelColor(int(-x * c + y * s) + center.x(), int(-x * s - y * c)+1 + center.y(), *color);
        if (p < 0)
        {
            p += 2 * b * b * x + 3 * b * b;
        }
        else
        {
            p +=  2 * b * b * x + 3 * b * b - 2 * a * a * y + a * a;
            y--;
        }
        x++;
    }
    int p1 = b * b * x * x + b * b * x + b * b / 4 + a * a * y * y - 2 * a * a * y + a * a - a * a * b * b;

    while (y >= 0)
    {
        //image->setPixelColor(x + center.x(), y + center.y(), *color);
        //image->setPixelColor(-x + center.x(), y + center.y(), *color);
        //image->setPixelColor(x + center.x(), -y + center.y(), *color);
        //image->setPixelColor(-x + center.x(), -y + center.y(), *color);
        image->setPixelColor(int(x * c - y * s) + center.x(), int(x * s + y * c) + center.y(), *color);
        image->setPixelColor(int(-x * c - y * s) + center.x(), int(-x * s + y * c) + center.y(), *color);
        image->setPixelColor(int(x * c + y * s) + center.x(), int(x * s - y * c) + center.y(), *color);
        image->setPixelColor(int(-x * c + y * s) + center.x(), int(-x * s - y * c) + center.y(), *color);
        image->setPixelColor(int(x * c - y * s)+1 + center.x(), int(x * s + y * c) + center.y(), *color);
        image->setPixelColor(int(-x * c - y * s)+1 + center.x(), int(-x * s + y * c) + center.y(), *color);
        image->setPixelColor(int(x * c + y * s)+1 + center.x(), int(x * s - y * c) + center.y(), *color);
        image->setPixelColor(int(-x * c + y * s)+1 + center.x(), int(-x * s - y * c) + center.y(), *color);
        image->setPixelColor(int(x * c - y * s) + center.x(), int(x * s + y * c)+1 + center.y(), *color);
        image->setPixelColor(int(-x * c - y * s) + center.x(), int(-x * s + y * c)+1 + center.y(), *color);
        image->setPixelColor(int(x * c + y * s) + center.x(), int(x * s - y * c)+1 + center.y(), *color);
        image->setPixelColor(int(-x * c + y * s) + center.x(), int(-x * s - y * c)+1 + center.y(), *color);
        if (p1 >= 0)
        {
            p1 += 3 * a * a - 2 * a * a * y;
        }
        else
        {
            p1 += 3 * a * a + 2 * b * b * x + 2 * b * b - 2 * a * a * y;
            x++;
        }
        y--;
    }
    /*int sqa = a * a;
    int sqb = b * b;
    int x = 0;
    int y = b;
    int d = 2 * sqb - 2 * b * sqa + sqa;
    while ((sqa + sqb) * x * x <= sqa * sqa)
    {
        image->setPixelColor(x + center.x(), y + center.y(), *color);
        image->setPixelColor(-x + center.x(), y + center.y(), *color);
        image->setPixelColor(x + center.x(), -y + center.y(), *color);
        image->setPixelColor(-x + center.x(), -y + center.y(), *color);
        if (d < 0)
        {
            d += 2 * sqb * (2 * x + 3);
        }
        else
        {
            d += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
            y--;
        }
        x++;
    }
    d = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
    while (y >= 0)
    {
        image->setPixelColor(x + center.x(), y + center.y(), *color);
        image->setPixelColor(-x + center.x(), y + center.y(), *color);
        image->setPixelColor(x + center.x(), -y + center.y(), *color);
        image->setPixelColor(-x + center.x(), -y + center.y(), *color);
        y--;
        if (d < 0)
        {
            x++;
            d = d - 2 * sqa * y - sqa + 2 * sqb * x + 2 * sqb;
        }
        else
        {
            d = d - 2 * sqa * y - sqa;
        }
    }*/
}
