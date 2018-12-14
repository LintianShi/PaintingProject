#ifndef PAINTINGPROJECT_H
#define PAINTINGPROJECT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QColorDialog>
#include "drawingarea.h"


namespace Ui {
class PaintingProject;
}

class PaintingProject : public QDialog
{
    Q_OBJECT

public:
    explicit PaintingProject(QWidget *parent = 0);
    //PaintingProject(QWidget *parent, MyShape* shape, QColor* color);
    ~PaintingProject();
    void loadImage();
    void loadImage(QString path);
    void loadImage(QImage* load_image);
    void saveImage();
    void setColor();
    void setShape(MyShape* shape);
    void hideToolBar();
    void myDraw();
    void myDrawLine();
    void myDrawCircle();
    void myDrawCurve();
    void myDrawOval();
    void mySetCircle();
    void mySetLine();
    void mySetOval();
    void myDrawPoly();
    void myFill();
    void myEdit();
    void myTailor();

private:
    Ui::PaintingProject *ui;
    QToolBar* myToolbar;
    QMainWindow* mainWindow;
    DrawingArea* drawArea;
    QAction* drawLine;
    QAction* drawCurve;
    QAction* drawCircle;
    QAction* drawOval;
    //QAction* drawRectangle;
    QAction* drawPen;
    QAction* color;
    QAction* open;
    QAction* save;
    QAction* drawFill;
    QAction* edit;
    QAction* drawPoly;
    QAction* tailor;
    void TODO();
};

#endif // PAINTINGPROJECT_H
