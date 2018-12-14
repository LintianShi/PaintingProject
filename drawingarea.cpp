#include "drawingarea.h"
#include "ui_drawingarea.h"
#include "myline.h"
#include "mycircle.h"
#include "myoval.h"
#include "mypolygon.h"
#include "paintingproject.h"
#include <QDebug>
#include <cmath>
#include <queue>
#include <stack>
#include <QInputDialog>
using namespace std;

DrawingArea::DrawingArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawingArea)
{
    ui->setupUi(this);
    //pix = new QPixmap(1275,667);
    //pix->fill(Qt::white);
    image = new QImage(WIDTH, HEIGHT, QImage::Format_RGB32);
    image->fill(Qt::white);
    background = new QImage(WIDTH, HEIGHT, QImage::Format_RGB32);
    background->fill(Qt::white);

    pen = new QPen();
    pen->setWidth(1);
    penColor = new QColor(Qt::black);
    pen->setColor(*penColor);

    state = BLANK;

    rightPressMenu = new QMenu;
    translation = new QAction("平移",this);
    rotate = new QAction("旋转",this);
    zoom = new QAction("缩放",this);
    undo = new QAction("撤销", this);
    //rotate = new QAction("旋转",this);
    rightPressMenu->addAction(translation);
    rightPressMenu->addAction(rotate);
    rightPressMenu->addAction(zoom);
    rightPressMenu->addAction(undo);
    connect(undo, &QAction::triggered, this, &DrawingArea::undoImage);
    connect(translation, &QAction::triggered, this, &DrawingArea::translateImage);
    connect(zoom, &QAction::triggered, this, &DrawingArea::zoomImage);
    connect(rotate, &QAction::triggered, this, &DrawingArea::rotateImage);

    current = NULL;
    begin.setX(0);
    begin.setY(0);
    end.setX(0);
    end.setY(0);
}



DrawingArea::~DrawingArea()
{
    delete pen;
    delete penColor;
    delete pix;
    delete ui;
    delete image;
}

void DrawingArea::paintEvent(QPaintEvent* e) {
    //qDebug()<<penColor->name();
    QPainter painter(this);
    painter.drawImage(0,0,*image);
}

void DrawingArea::loadImage(QString path)
{
    image->load(path);
    *image = image->scaled(WIDTH, HEIGHT);
    *background = *image;
}

void DrawingArea::loadImage(QImage *load_image)
{
    *image = *load_image;
    *background = *load_image;
}

void DrawingArea::saveImage(QString path)
{
    image->save(path);
}

void DrawingArea::setColor(const QColor& color)
{
    *penColor = color;
    //pen->setColor(*penColor);
}

void DrawingArea::undoImage()
{
    *image = *background;
    current = NULL;
    update();
}

void DrawingArea::saveChange()
{
    if (current != NULL)
    {
        *image = *background;
        current->draw(image, penColor);
        update();
    }

    *background = *image;
    current = NULL;
    MyOval::angle = 0;
}

void DrawingArea::translateImage()
{
    if (current != NULL)
    {
        int x = QInputDialog::getInt(NULL, tr("输入水平平移量"), tr("x:"));
        int y = QInputDialog::getInt(NULL, tr("输入垂直平移量"), tr("y:"));
        current->translate(x, y);
        *image = *background;
        current->draw(image, penColor);
        current->anchors(image);
        update();
    }
}

void DrawingArea::zoomImage()
{
    if (current != NULL)
    {
        int p = QInputDialog::getInt(NULL, tr("输入缩放比例(%)"), tr("缩放比例(%):"));
        //int y = QInputDialog::getInt(NULL, tr("输入垂直平移量"), tr("y:"));
        current->zoom(p);
        *image = *background;
        current->draw(image, penColor);
        current->anchors(image);
        update();
    }
}

void DrawingArea::rotateImage()
{
    if (current != NULL)
    {
        int a = QInputDialog::getInt(NULL, tr("输入旋转角度"), tr("旋转角度:"));
        current->rotate(a);
        *image = *background;
        current->draw(image, penColor);
        current->anchors(image);
        update();
    }
}

void DrawingArea::enterEvent(QEvent* e)
{
    qDebug()<<"here enterEvent";
    if (state == TAILOR)
    {
        setCursor(Qt::CrossCursor);
    }
    else if (state == DRAW)
    {
        QPixmap temp(":/image/image/bi.png");
        ;
        setCursor(QCursor(temp.scaled(30, 30),5,20));
    }
    else if (state == FILL)
    {
        QPixmap temp(":/image/image/youqitong.png");
        setCursor(QCursor(temp.scaled(30, 30),-1,-1));
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void DrawingArea::mouseDoubleClickEvent(QMouseEvent* e)
{
    if (state == POLYGON)
    {
        points.pop_back();
        if (points.empty())
        {
            return;
        }
        current = new MyPolygon(points);
        back.assign(points.begin(), points.end());
        points.clear();
        *image = *background;
        current->draw(image, penColor);
        current->anchors(image);
        update();
    }
    else if (state == CURVE)
    {
        points.pop_back();
        if (points.empty())
        {
            return;
        }
        current = new MyCurve(points);
        back.assign(points.begin(), points.end());
        points.clear();
        *image = *background;
        current->draw(image, penColor);
        current->anchors(image);
        update();
    }
}

void DrawingArea::mousePressEvent(QMouseEvent* e)
{
    qDebug()<<"here press";
    if(e->button()==Qt::LeftButton) //鼠标左键按下
    {
        qDebug()<<"here left press";
        if (current != NULL)
        {
            qDebug()<<"1";
            end = current->getSelectedAnchor(e->pos());
            if (end.x() != -1 && end.y() != -1)
            {
                state = current->getShapeKind();
                begin = current->getFixedAnchor(e->pos());
                return;
            }
        }
        qDebug()<<"2";
        begin = e->pos();
        if (state == POLYGON)
        {
            if (points.empty())
            {
                saveChange();
            }
            points.push_back(begin);
            *image = *background;
            MyPolygon temp(points);
            temp.drawTemp(image, penColor);
            return;
        }
        else if (state == CURVE)
        {
            if (points.empty())
            {
                saveChange();
            }
            points.push_back(begin);
            *image = *background;
            MyCurve temp(points);
            temp.draw(image, penColor);
            temp.anchors(image);
            return;
        }
        end = begin;
        if (state == TAILOR && current != NULL && current->getShapeKind() == LINE)
        {
            ;
        }
        else
        {
            qDebug()<<"4";
            saveChange();
        }
        qDebug()<<"press";

    }
    else if (e->button() == Qt::RightButton)
    {
        if (current != NULL)
        {
            *image = *background;
            current->draw(image, penColor);
            update();
        }
        rightPressMenu->exec(e->globalPos());

    }
    qDebug()<<"here press end";
}

void DrawingArea::mouseMoveEvent(QMouseEvent* e)
{
    if(e->buttons()&Qt::LeftButton)
    {
        qDebug()<<"press";
         end = e->pos();

        if (state == DRAW)
        {
            MyLine myLine(begin, end);
            myLine.draw(image,penColor);
            *background = *image;
            update();
            begin = end;
        }
        else if (state == LINE)
        {
            //qDebug()<<begin<<' '<<end;
            MyLine temp(begin, end);
            *image = *background;
            temp.draw(image, penColor);
        }
        else if (state == CIRCLE)
        {
            //double r = sqrt((double)(begin.x() - end.x()) * (begin.x() - end.x()) + (begin.y() - end.y()) * (begin.y() - end.y()));
            MyCircle temp((begin.x() + end.x()) / 2, (begin.y() + end.y()) / 2, abs(begin.x() - end.x()) / 2);
            *image = *background;
            temp.draw(image, penColor);
        }
        else if (state == OVAL)
        {
            MyOval temp((begin.x() + end.x()) / 2, (begin.y() + end.y()) / 2, abs(end.x() - begin.x()) / 2, abs(end.y() - begin.y()) / 2);
            //myOval.draw(image, penColor);
            *image = *background;
            temp.draw(image, penColor);
        }
        else if (state == TAILOR)
        {
            *image = *background;
            QPainter painter(image);
            QPen pen;
            //pen.setBrush(QBrush(Qt::blue));//设置笔刷，你可以不用设置
            QVector<qreal> dashes;
            qreal space = 3;
            dashes << 5 << space << 5 <<space;
            pen.setDashPattern(dashes);
            //pen.setWidth(2);
            painter.setPen(pen);
            int xmin = begin.x() < end.x() ? begin.x() : end.x();
            int xmax = begin.x() > end.x() ? begin.x() : end.x();
            int ymin = begin.y() < end.y() ? begin.y() : end.y();
            int ymax = begin.y() > end.y() ? begin.y() : end.y();
            painter.drawRect(xmin, ymin, xmax-xmin, ymax-ymin);
            if (current != NULL)
            {
                current->draw(image, penColor);
            }
        }
        qDebug()<<"move";
        update();
    }

}

void DrawingArea::mouseReleaseEvent(QMouseEvent* e)
{
    if(e->button()==Qt::LeftButton)
    {
        end = e->pos();
        if (state == BLANK)
        {
            return;
        }
        else if (state == DRAW)
        {
            MyLine myLine(begin, end);
            myLine.draw(image,penColor);
            *background = *image;
            current = NULL;
        }
        else if (state == LINE)
        {
            //qDebug()<<begin<<' '<<end;
            current = new MyLine(begin, end);
            *image = *background;
            current->draw(image, penColor);
            current->anchors(image);
        }
        else if (state == CIRCLE)
        {
            //double r = sqrt((double)(begin.x() - end.x()) * (begin.x() - end.x()) + (begin.y() - end.y()) * (begin.y() - end.y()));
            current = new MyCircle((begin.x() + end.x()) / 2, (begin.y() + end.y()) / 2, abs(begin.x() - end.x()) / 2);
            *image = *background;
            current->draw(image, penColor);
            current->anchors(image);

        }
        else if (state == OVAL)
        {
            current = new MyOval((begin.x() + end.x()) / 2, (begin.y() + end.y()) / 2, abs(end.x() - begin.x()) / 2, abs(end.y() - begin.y()) / 2);
            //myOval.draw(image, penColor);
            *image = *background;
            current->draw(image, penColor);
            current->anchors(image);
        }
        else if (state == FILL)
        {
            fill(end, penColor);
            *background = *image;
            current = NULL;
        }
        else if (state == TAILOR)
        {
            qDebug()<<"fill";
            if (current != NULL)
            {
                current->draw(image, penColor);
            }
            int xmin = begin.x() < end.x() ? begin.x() : end.x();
            int xmax = begin.x() > end.x() ? begin.x() : end.x();
            int ymin = begin.y() < end.y() ? begin.y() : end.y();
            int ymax = begin.y() > end.y() ? begin.y() : end.y();
            QImage* temp = new QImage();
            *temp = background->copy(xmin, ymin, xmax-xmin, ymax-ymin);
            PaintingProject* newProject = new PaintingProject();
            newProject->setWindowModality(Qt::ApplicationModal);
            newProject->show();
            newProject->loadImage(temp);
            if (current != NULL)
            {
                MyLine* temp = dynamic_cast<MyLine*>(current);
                /*if (temp->getBegin().x() >= xmin && temp->getBegin().x() <= xmax
                        && temp->getEnd().x() >= xmin && temp->getEnd().x() <= xmax )
                {
                    MyLine* line = new MyLine(temp->getBegin().x()-xmin, temp->getBegin().y()-ymin,
                                              temp->getEnd().x()-xmin, temp->getEnd().y()-ymin);
                }*/

                MyLine* line = tailor(temp, xmin, xmax, ymin, ymax);
                newProject->setShape(line);
            }

            *image = *background;
            if (current != NULL)
            {
                current->draw(image, penColor);
                current = NULL;
            }
            //state == BLANK;
            qDebug()<<"hi";
            //saveChange();

        }
        else if (state == POLYGON && points.empty() && current != NULL)
        {
            MyPolygon* temp = dynamic_cast<MyPolygon*>(current);
            temp->change(begin, end);
            *image = *background;
            current->draw(image, penColor);
            current->anchors(image);
        }
        else if (state == CURVE && points.empty() && current != NULL)
        {
            MyCurve* temp = dynamic_cast<MyCurve*>(current);
            temp->change(begin, end);
            *image = *background;
            current->draw(image, penColor);
            current->anchors(image);
        }
        update();
        qDebug()<<"hello";
    }
}

void DrawingArea::setFunction(FUNCTION function)
{
    state = function;
    qDebug()<<state;
}

void DrawingArea::setShape(MyShape* shape)
{
    current = shape;
    if (current != NULL)
    {
        current->draw(image, penColor);
        current->anchors(image);
    }

}

void DrawingArea::fill(QPoint p, QColor *color)
{
    
    stack<QPoint> s;
    QColor newColor = *color;
    QColor oldColor = image->pixelColor(p);
    bool left = false;
    bool right = false;
    //int y = p.y();
    s.push(p);
    while (!s.empty())
    {
        QPoint temp = s.top();
        s.pop();
        qDebug()<<temp;
        int x = temp.x();
        int y = temp.y();
        while (y >= 0 && image->pixelColor(x, y) == oldColor)
        {
            y--;
        }
        y++;
        left = false;
        right = false;
        while (y < HEIGHT && image->pixelColor(x, y) == oldColor)
        {
            image->setPixelColor(x, y, newColor);
            if (!left && x > 0 && image->pixelColor(x - 1, y) == oldColor)
            {
                s.push(QPoint(x - 1, y));
                left = true;
            }
            else if (left && x > 0 && image->pixelColor(x - 1, y) != oldColor)
            {
                left = false;
            }
            if (!right && x < WIDTH - 1 && image->pixelColor(x + 1, y) == oldColor)
            {
                s.push(QPoint(x + 1, y));
                right = true;
            }
            else if (right && x < WIDTH - 1 && image->pixelColor(x + 1, y) != oldColor)
            {
                right = false;
            }
            y++;
        }

    }

}

MyLine* DrawingArea::tailor(MyLine *line, int xmin, int xmax, int ymin, int ymax)
{
    bool flag_begin = false;
    bool flag_end = false;
    int x1 = line->getBegin().x() < line->getEnd().x() ? line->getBegin().x() : line->getEnd().x();
    int x2 = line->getBegin().x() >= line->getEnd().x() ? line->getBegin().x() : line->getEnd().x();
    if (line->getBegin().x() >= xmin && line->getBegin().x() <= xmax
            && line->getBegin().y() >= ymin && line->getBegin().y() <= ymax )
    {
        flag_begin = true;
    }
    if (line->getEnd().y() >= ymin && line->getEnd().y() <= ymax
            && line->getEnd().x() >= xmin && line->getEnd().x() <= xmax )
    {
        flag_end = true;
    }
    if (flag_begin && flag_end)
    {
        MyLine* temp = new MyLine(line->getBegin().x()-xmin, line->getBegin().y()-ymin,
                                  line->getEnd().x()-xmin, line->getEnd().y()-ymin);
        return temp;
    }
    else
    {
        int a = line->getEnd().y() - line->getBegin().y();
        int b = line->getBegin().x() - line->getEnd().x();
        int c = line->getEnd().x() * line->getBegin().y() - line->getBegin().x() * line->getEnd().y();
        if (!flag_begin && flag_end)
        {
            QPoint p[4];
            p[0] = QPoint(xmin, (-c-a*xmin)/b);
            p[1] = QPoint(xmax, (-c-a*xmax)/b);
            p[2] = QPoint((-c-b*ymin)/a, ymin);
            p[3] = QPoint((-c-b*ymax)/a, ymax);
            int i;
            for (i = 0; i < 4; i++)
            {
                if (p[i].x() >= xmin && p[i].x() <= xmax && p[i].y() >= ymin && p[i].y() <= ymax
                        && p[i].x() >= x1 && p[i].x() <= x2)
                {
                    MyLine* temp = new MyLine(line->getEnd().x() - xmin, line->getEnd().y() - ymin,
                                              p[i].x() - xmin, p[i].y() - ymin);
                    return temp;
                }
            }
        }
        else if (flag_begin && !flag_end)
        {
            qDebug()<<"!end";
            QPoint p[4];
            p[0] = QPoint(xmin, (-c-a*xmin)/b);
            p[1] = QPoint(xmax, (-c-a*xmax)/b);
            p[2] = QPoint((-c-b*ymin)/a, ymin);
            p[3] = QPoint((-c-b*ymax)/a, ymax);
            int i;
            for (i = 0; i < 4; i++)
            {
                if (p[i].x() >= xmin && p[i].x() <= xmax && p[i].y() >= ymin && p[i].y() <= ymax
                        && p[i].x() >= x1 && p[i].x() <= x2)
                {
                    MyLine* temp = new MyLine(line->getBegin().x() - xmin, line->getBegin().y() - ymin,
                                              p[i].x() - xmin, p[i].y() - ymin);
                    return temp;
                }
            }
        }
        else
        {
            QPoint p[4];
            p[0] = QPoint(xmin, (-c-a*xmin)/b);
            p[1] = QPoint(xmax, (-c-a*xmax)/b);
            p[2] = QPoint((-c-b*ymin)/a, ymin);
            p[3] = QPoint((-c-b*ymax)/a, ymax);
            int i;
            int j = 0;
            int t[2] = {-1, -1};
            for (i = 0; i < 4; i++)
            {
                if (p[i].x() >= xmin && p[i].x() <= xmax && p[i].y() >= ymin && p[i].y() <= ymax
                        && p[i].x() >= x1 && p[i].x() <= x2)
                {
                    t[j] = i;
                    j++;
                    qDebug()<<"yes";
                }
            }
            if (t[0] >= 0 && t[1] >= 0)
            {
                MyLine* temp = new MyLine(p[t[0]].x() - xmin, p[t[0]].y() - ymin,
                        p[t[1]].x() - xmin, p[t[1]].y() - ymin);
                return temp;
            }
            else
            {
                return NULL;
            }
        }
    }
}
