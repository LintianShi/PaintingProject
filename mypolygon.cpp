#include "mypolygon.h"
#include "myline.h"
#include <QDebug>
#include <QPainter>

MyPolygon::MyPolygon(vector<QPoint> p):
    vertex(p)
{
    int i = 0;
    for (i = 0; i < vertex.size(); i++)
    {
        qDebug()<<vertex[i];
    }
}

QPoint MyPolygon::getMidPoint()
{
    int minX = vertex[0].x();
    int maxX = vertex[0].x();
    int minY = vertex[0].y();
    int maxY = vertex[0].y();
    int i = 0;
    for (i = 1; i < vertex.size(); i++)
    {
        if (vertex[i].x() > maxX)
        {
            maxX = vertex[i].x();
        }
        if (vertex[i].x() < minX)
        {
            minX = vertex[i].x();
        }
        if (vertex[i].y() > maxY)
        {
            maxY = vertex[i].y();
        }
        if (vertex[i].y() < minY)
        {
            minY = vertex[i].y();
        }
    }
    return QPoint((maxX + minX) / 2, (maxY + minY) / 2);
}

void MyPolygon::draw(QImage* image, QColor* color)
{
    int i = 0;
    for (i = 0; i < vertex.size() - 1; i++)
    {
        qDebug()<<vertex[i];
        MyLine temp(vertex[i], vertex[i+1]);
        temp.draw(image, color);
    }
    MyLine temp(vertex[vertex.size() - 1], vertex[0]);
    temp.draw(image, color);
}

void MyPolygon::translate(int x, int y)
{
    int i = 0;
    for (i = 0; i < vertex.size(); i++)
    {
        vertex[i].setX(vertex[i].x() + x);
        vertex[i].setY(vertex[i].y() + y);
    }
}

void MyPolygon::zoom(int p)
{
    double z = double(p) / 100;
    QPoint mid = getMidPoint();
    int i = 0;
    for (i = 0; i < vertex.size(); i++)
    {
        vertex[i].setX(mid.x() + (vertex[i].x() - mid.x()) * z);
        vertex[i].setY(mid.y() + (vertex[i].y() - mid.y()) * z);
    }
}

void MyPolygon::drawTemp(QImage* image, QColor* color)
{

        int i = 0;
        for (i = 0; i < vertex.size() - 1; i++)
        {
            //qDebug()<<vertex[i];
            MyLine temp(vertex[i], vertex[i+1]);
            temp.draw(image, color);
        }
        QPainter* painter = new QPainter(image);
        painter->setPen(Qt::black);
        painter->setBrush(Qt::black);
        //int i = 0;
        for (i = 0; i < vertex.size(); i++)
        {
            painter->drawRect(vertex[i].x(), vertex[i].y(), 5, 5);
            //painter->drawRect(end.x(), end.y(), 5, 5);
        }
        delete painter;

}

void MyPolygon::rotate(int angle)
{
    double c = cos(double(angle) * 3.1415926 / 180);
    double s = sin(double(angle) * 3.1415926 / 180);
    QPoint mid = getMidPoint();
    int i = 0;
    for (i = 0; i < vertex.size(); i++)
    {
        int x = vertex[i].x();
        int y = vertex[i].y();
        vertex[i].setX(mid.x() + (x - mid.x()) * c - (y - mid.y()) * s);
        vertex[i].setY(mid.y() + (x - mid.x()) * s + (y - mid.y()) * c);
    }
}

void MyPolygon::anchors(QImage* image)
{
    QPainter* painter = new QPainter(image);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    int i = 0;
    for (i = 0; i < vertex.size(); i++)
    {
        painter->drawRect(vertex[i].x(), vertex[i].y(), 5, 5);
        //painter->drawRect(end.x(), end.y(), 5, 5);
    }
    delete painter;
}

FUNCTION MyPolygon::getShapeKind()
{
    return POLYGON;
}

QPoint MyPolygon::getSelectedAnchor(QPoint p)
{
    int d = distance(vertex[0], p);
    //qDebug()<<d<<"????";
    int min = 0;
    int i = 0;
    for (i = 1; i < vertex.size(); i++)
    {
        //qDebug()<<vertex[i]<<"????";
        if (distance(vertex[i], p) < d)
        {
            d = distance(vertex[i], p);
            min = i;
        }
    }
    if (d <= 144)
    {
        return vertex[min];
    }
    else
    {
        return QPoint(-1, -1);
    }
}

QPoint MyPolygon::getFixedAnchor(QPoint p)
{
    return getSelectedAnchor(p);
}

void MyPolygon::change(QPoint before, QPoint after)
{
    int i = 0;
    for (i = 0; i < vertex.size(); i++)
    {
        if (vertex[i] == before)
        {
            vertex[i] = after;
            return;
        }
    }
}
