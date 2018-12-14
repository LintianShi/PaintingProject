#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QPaintEvent>
#include <QFileDialog>
#include <QPoint>
#include <QMenu>
#include <QDebug>
#include <vector>
#include "function.h"
#include "myshape.h"
#include "myline.h"
#include "mycurve.h"
using namespace std;

#define WIDTH 1275
#define HEIGHT 667

namespace Ui {
class DrawingArea;
}

class DrawingArea : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingArea(QWidget *parent = 0);
    ~DrawingArea();
    void loadImage(QString path);
    void saveImage(QString path);
    void loadImage(QImage* load_image);
    void setColor(const QColor& color);
    void setFunction(FUNCTION function);
    void setShape(MyShape* shape);
    void fill(QPoint p, QColor* color);
    void undoImage();
    void translateImage();
    void zoomImage();
    void rotateImage();
    void saveChange();
    MyLine* tailor(MyLine* line, int xmin, int xmax, int ymin, int ymax);

protected:
    void paintEvent(QPaintEvent* );
    void enterEvent(QEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::DrawingArea *ui;
    QPixmap* pix;
    QImage* image;
    QImage* background;
    QColor* penColor;
    QPen* pen;
    int penWidth;
    QPoint begin;
    QPoint end;
    FUNCTION state;
    QMenu* rightPressMenu;
    QAction* translation;
    QAction* rotate;
    QAction* zoom;
    QAction* undo;
    MyShape* current;
    vector<QPoint> points;
    vector<QPoint> back;
};

#endif // DRAWINGAREA_H
