#include "mycurve.h"
#include <QPainter>
MyCurve::MyCurve()
{
    ;
}

MyCurve::MyCurve(vector<QPoint> points)
{
    np = points.size();
    jd.push_back(points[0]);
    for (int i = 0; i < np; i++)
    {
        jd.push_back(points[i]);
    }
    jd.push_back(points[np-1]);
    np += 2;
    grain = 500;
    tension = 0.5;
    mc[0]=-tension; mc[1]=2.0-tension; mc[2]=tension-2.; mc[3]=tension;
    mc[4]=2.0*tension; mc[5]=tension-3.0; mc[8]=-tension; mc[9]=0.0;
    mc[12]=0.; mc[13]=1.; mc[6]=3.0-2*tension; mc[7]=-tension;
    mc[10]=tension; mc[11]=0.0; mc[14]=0.0; mc[15]=0.0;
}

void MyCurve::draw(QImage* image, QColor* color)
{
    vector<double> alpha;
    for (int i = 0; i < grain; i++)
    {
        alpha.push_back(i*1.0/grain);
    }
    int kml = 0;
    int k0 = 1;
    int k1 = 2;
    int k2 = 3;

    for(int i =1; i< np-2; i++){
            for(int j=0; j<grain; j++){
                double cpx = getMatrix(jd[kml].x(), jd[k0].x(), jd[k1].x(), jd[k2].x(), alpha[j]);
                double cpy = getMatrix(jd[kml].y(), jd[k0].y(), jd[k1].y(), jd[k2].y(), alpha[j]);
                image->setPixelColor(cpx, cpy, *color);
            }
            kml++; k0++; k1++; k2++;
        }
}

double MyCurve::getMatrix(double p0, double p1, double p2, double p3, double u)
{
    double a=mc[0]*p0+mc[1]*p1+mc[2]*p2+mc[3]*p3;
    double b=mc[4]*p0+mc[5]*p1+mc[6]*p2+mc[7]*p3;
    double c=mc[8]*p0+mc[9]*p1+mc[10]*p2+mc[11]*p3;
    double d=mc[12]*p0+mc[13]*p1+mc[14]*p2+mc[15]*p3;
    return(d+u*(c+u*(b+u*a))); //au^3+bu^2+cu+d
}


FUNCTION MyCurve::getShapeKind()
{
    return CURVE;
}

void MyCurve::translate(int x, int y)
{
    for (int i = 0; i < jd.size(); i++)
    {
        jd[i].setX(x+jd[i].x());
        jd[i].setY(y+jd[i].y());
    }
}
QPoint MyCurve::getMidPoint()
{
    int minX = jd[0].x();
    int maxX = jd[0].x();
    int minY = jd[0].y();
    int maxY = jd[0].y();
    int i = 0;
    for (i = 1; i < jd.size(); i++)
    {
        if (jd[i].x() > maxX)
        {
            maxX = jd[i].x();
        }
        if (jd[i].x() < minX)
        {
            minX = jd[i].x();
        }
        if (jd[i].y() > maxY)
        {
            maxY = jd[i].y();
        }
        if (jd[i].y() < minY)
        {
            minY = jd[i].y();
        }
    }
    return QPoint((maxX + minX) / 2, (maxY + minY) / 2);
}
void MyCurve::zoom(int p)
{
    double z = double(p) / 100;
    QPoint mid = getMidPoint();
    int i = 0;
    for (i = 0; i < jd.size(); i++)
    {
        jd[i].setX(mid.x() + (jd[i].x() - mid.x()) * z);
        jd[i].setY(mid.y() + (jd[i].y() - mid.y()) * z);
    }
}
void MyCurve::rotate(int angle)
{
    double c = cos(double(angle) * 3.1415926 / 180);
    double s = sin(double(angle) * 3.1415926 / 180);
    QPoint mid = getMidPoint();
    int i = 0;
    for (i = 0; i < jd.size(); i++)
    {
        int x = jd[i].x();
        int y = jd[i].y();
        jd[i].setX(mid.x() + (x - mid.x()) * c - (y - mid.y()) * s);
        jd[i].setY(mid.y() + (x - mid.x()) * s + (y - mid.y()) * c);
    }
}
void MyCurve::anchors(QImage* image)
{
    QPainter* painter = new QPainter(image);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    for (int i = 1; i < jd.size()-1; i++)
    {
        painter->drawRect(jd[i].x(), jd[i].y(), 5, 5);
    }
    delete painter;
}

QPoint MyCurve::getSelectedAnchor(QPoint p)
{
    int d = distance(jd[0], p);
    //qDebug()<<d<<"????";
    int min = 0;
    int i = 0;
    for (i = 1; i < jd.size(); i++)
    {
        //qDebug()<<vertex[i]<<"????";
        if (distance(jd[i], p) < d)
        {
            d = distance(jd[i], p);
            min = i;
        }
    }
    if (d <= 144)
    {
        return jd[min];
    }
    else
    {
        return QPoint(-1, -1);
    }
}

QPoint MyCurve::getFixedAnchor(QPoint p)
{
    return getSelectedAnchor(p);
}

void MyCurve::change(QPoint before, QPoint after)
{
    int i = 0;
    for (i = 0; i < jd.size(); i++)
    {
        if (jd[i] == before)
        {
            jd[i] = after;
            //return;
        }
    }
}
