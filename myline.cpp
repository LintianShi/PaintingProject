#include "myline.h"
#include <QPainter>
#include <cmath>
#include <QDebug>
using namespace std;
MyLine::MyLine():
    begin(0, 0), end(0, 0)
{
    ;
}

MyLine::MyLine(int x0, int y0, int x1, int y1):
    begin(x0, y0), end(x1, y1)
{
    ;
}

MyLine::MyLine(QPoint p0, QPoint p1):
    begin(p0), end(p1)
{
    ;
}

QPoint MyLine::getBegin()
{
    return begin;
}

QPoint MyLine::getEnd()
{
    return end;
}

FUNCTION MyLine::getShapeKind()
{
    return LINE;
}

QPoint MyLine::getFixedAnchor(QPoint p)
{
    int d1 = (abs(p.x() - begin.x())) * (abs(p.x() - begin.x())) + (abs(p.y() - begin.y())) * (abs(p.y() - begin.y()));
    int d2 = (abs(p.x() - end.x())) * (abs(p.x() - end.x())) + (abs(p.y() - end.y())) * (abs(p.y() - end.y()));
    if (d1 > d2)
    {
        return begin;
    }
    else
    {
        return end;
    }
}

QPoint MyLine::getSelectedAnchor(QPoint p)
{
    int d1 = (abs(p.x() - begin.x())) * (abs(p.x() - begin.x())) + (abs(p.y() - begin.y())) * (abs(p.y() - begin.y()));
    int d2 = (abs(p.x() - end.x())) * (abs(p.x() - end.x())) + (abs(p.y() - end.y())) * (abs(p.y() - end.y()));
    if (d1 < d2 && d1 <= 144)
    {
        return begin;
    }
    else if (d2 <= d1 && d2 <= 144)
    {
        return end;
    }
    else
    {
        return QPoint(-1, -1);
    }
}

void MyLine::translate(int x, int y)
{
    begin.setX(begin.x() + x);
    begin.setY(begin.y() + y);
    end.setX(end.x() + x);
    end.setY(end.y() + y);
}

void MyLine::zoom(int p)
{
    if (p > 0)
    {
        double z = double(p) / 100;
        int mid_x = (begin.x() + end.x()) / 2;
        int mid_y = (begin.y() + end.y()) / 2;
        int x1 = begin.x() - mid_x;
        int x2 = end.x() - mid_x;
        int y1 = begin.y() - mid_y;
        int y2 = end.y() - mid_y;
        begin.setX(mid_x + int(x1*z));
        end.setX(mid_x + int(x2*z));
        begin.setY(mid_y + int(y1*z));
        end.setY(mid_y + int(y2*z));
    }
}

void MyLine::rotate(int angle)
{
    double c = cos(double(angle) * 3.1415926 / 180);
    double s = sin(double(angle) * 3.1415926 / 180);
    int mid_x = (begin.x() + end.x()) / 2;
    int mid_y = (begin.y() + end.y()) / 2;
    int x1 = begin.x();
    int x2 = end.x();
    int y1 = begin.y();
    int y2 = end.y();
    begin.setX(int(mid_x + (x1 - mid_x) * c - (y1 - mid_y) * s));
    begin.setY(int(mid_y + (x1 - mid_x) * s + (y1 - mid_y) * c));
    end.setX(int(mid_x + (x2 - mid_x) * c - (y2 - mid_y) * s));
    end.setY(int(mid_y + (x2 - mid_x) * s + (y2 - mid_y) * c));
}

void MyLine::anchors(QImage* image)
{
    QPainter* painter = new QPainter(image);
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->drawRect(begin.x(), begin.y(), 5, 5);
    painter->drawRect(end.x(), end.y(), 5, 5);
    delete painter;
}

void MyLine::draw(QImage* image, QColor* color)
{
    int x1 = begin.x();
    int y1 = begin.y();
    int x2 = end.x();
    int y2 = end.y();

    if (x2 < x1)
    {
        int temp = x2;
        x2 = x1;
        x1 = temp;
        temp = y2;
        y2 = y1;
        y1 = temp;
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x = x1;
    int y = y1;

    if (dy >= 0 && dy <= dx)
    {
        int p = dy * 2 - dx;
        for ( ; x <= x2; x++)
        {
            image->setPixelColor(x, y, *color);
            //painter.drawPoint(x, y);
            if (p >= 0)
            {
                y++;
                p += 2 * (dy - dx);
            }
            else
            {
                p += 2 * dy;
            }
        }
    }
    else if (dy < 0 && -dy <= dx)
    {
        dy = -dy;
        int p = dy * 2 - dx;
        for ( ; x <= x2; x++)
        {
            //painter.drawPoint(x, y);
            image->setPixelColor(x, y, *color);
            if (p >= 0)
            {
                y--;
                p += 2 * (dy - dx);
            }
            else
            {
                p += 2 * dy;
            }
        }
    }
    else if (dy >= 0 && dy > dx)
    {
        y = y1;
        int p = dx * 2 - dy;
        for ( ; y <= y2; y++)
        {
           // painter.drawPoint(x, y);
            image->setPixelColor(x, y, *color);
            if (p >= 0)
            {
                x++;
                p += 2 * (dx - dy);
            }
            else
            {
                p += 2 * dx;
            }
        }
    }
    else if (dy < 0 && -dy > dx)
    {
        dy = -dy;
        y = y2;
        x = x2;
        int p = dx * 2 - dy;
        //qDebug()<<x;
        for ( ; y <= y1; y++)
        {
            //painter.drawPoint(x, y);
            image->setPixelColor(x, y, *color);
            if (p >= 0)
            {
                x--;
                p += 2 * (dx - dy);
            }
            else
            {
                p += 2 * dx;
            }
        }
    }
}
