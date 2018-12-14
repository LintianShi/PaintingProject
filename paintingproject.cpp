#include "paintingproject.h"
#include "ui_paintingproject.h"
#include <QInputDialog>
#include <QPushButton>
#include <QWidget>
#include "mycircle.h"
#include "myline.h"
#include "myoval.h"

PaintingProject::PaintingProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintingProject)
{
    ui->setupUi(this);

    setWindowTitle(tr("New Painting Project"));
    setWindowState(Qt::WindowMaximized);
    setWindowFlags(Qt::Window);
    mainWindow = new QMainWindow();
    this->resize(800, 600);
    //this->setWindowState(Qt::WindowMaximized);
    mainWindow->statusBar();

    myToolbar = new QToolBar();
    myToolbar->setMovable(false);
    myToolbar->setIconSize(QSize(39,39));
    myToolbar->setFixedWidth(50);
    myToolbar->setFloatable(false);

    mainWindow->addToolBar(Qt::LeftToolBarArea,myToolbar);

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(mainWindow);
    setLayout(layout);

    drawArea = new DrawingArea(mainWindow);
    mainWindow->setCentralWidget(drawArea);

    edit = new QAction(QIcon(":/image/image/edit.png"), tr("指针"), myToolbar);
    edit->setToolTip(tr("指针"));
    connect(edit, &QAction::triggered, this, &PaintingProject::myEdit);
    myToolbar->addAction(edit);

    drawPen = new QAction(QIcon(":/image/image/Pen.png"), tr("画笔"), myToolbar);
    drawPen->setToolTip(tr("画笔"));
    connect(drawPen, &QAction::triggered, this, &PaintingProject::myDraw);
    myToolbar->addAction(drawPen);

    drawFill = new QAction(QIcon(":/image/image/fill.png"), tr("填充"), myToolbar);
    drawFill->setToolTip(tr("填充"));
    connect(drawFill, &QAction::triggered, this, &PaintingProject::myFill);
    myToolbar->addAction(drawFill);

    tailor = new QAction(QIcon(":/image/image/tailor.png"), tr("剪裁"), myToolbar);
    tailor->setToolTip(tr("剪裁"));
    connect(tailor, &QAction::triggered, this, &PaintingProject::myTailor);
    myToolbar->addAction(tailor);

    drawLine = new QAction(QIcon(":/image/image/Line.png"), tr("直线"), myToolbar);
    //drawLine->setStatusTip(tr("直线"));
    drawLine->setToolTip(tr("直线"));
    connect(drawLine, &QAction::triggered, this, &PaintingProject::myDrawLine);
    myToolbar->addAction(drawLine);

    drawCurve = new QAction(QIcon(":/image/image/Curve.png"), tr("曲线"), myToolbar);
    drawCurve->setToolTip(tr("曲线"));
    connect(drawCurve, &QAction::triggered, this, &PaintingProject::myDrawCurve);
    myToolbar->addAction(drawCurve);

    /*drawRectangle = new QAction(QIcon(":/image/image/Rectangle.png"), tr("矩形"), myToolbar);
    drawRectangle->setToolTip(tr("矩形"));
    connect(drawRectangle, &QAction::triggered, this, &PaintingProject::TODO);
    myToolbar->addAction(drawRectangle);*/

    drawCircle = new QAction(QIcon(":/image/image/Circle.png"), tr("圆"), myToolbar);
    drawCircle->setToolTip(tr("圆"));
    connect(drawCircle, &QAction::triggered, this, &PaintingProject::myDrawCircle);
    myToolbar->addAction(drawCircle);

    drawOval = new QAction(QIcon(":/image/image/Oval.png"), tr("椭圆"), myToolbar);
    drawOval->setToolTip(tr("椭圆"));
    connect(drawOval, &QAction::triggered, this, &PaintingProject::myDrawOval);
    myToolbar->addAction(drawOval);

    drawPoly = new QAction(QIcon(":/image/image/poly.png"), tr("多边形"), myToolbar);
    drawPoly->setToolTip(tr("多边形"));
    connect(drawPoly, &QAction::triggered, this, &PaintingProject::myDrawPoly);
    myToolbar->addAction(drawPoly);

    color = new QAction(QIcon(":/image/image/color.png"), tr("颜色"), myToolbar);
    color->setToolTip(tr("颜色"));
    connect(color, &QAction::triggered, this, PaintingProject::setColor);
    myToolbar->addAction(color);

    save = new QAction(QIcon(":/image/image/Save.png"), tr("保存"), myToolbar);
    save->setToolTip(tr("保存"));
    connect(save, &QAction::triggered, this, &PaintingProject::saveImage);
    myToolbar->addAction(save);

    open = new QAction(QIcon(":/image/image/OpenFile.png"), tr("打开"), myToolbar);
    open->setToolTip(tr("打开"));
    void (PaintingProject:: *load)() = &PaintingProject::loadImage;
    connect(open, &QAction::triggered, this, load);
    myToolbar->addAction(open);


}

PaintingProject::~PaintingProject()
{
    delete myToolbar;
    delete mainWindow;
    delete drawArea;
    delete drawLine;
    delete drawCurve;
    delete drawCircle;
    delete drawOval;
    //delete drawRectangle;
    delete drawPen;
    delete save;
    delete open;
    delete color;
    delete ui;
}

void PaintingProject::TODO()
{
    qDebug()<<"to do";
    QPushButton* circle = new QPushButton("圆", NULL);
    QPushButton* oval = new QPushButton("椭圆", NULL);
    QPushButton* line = new QPushButton("直线", NULL);
    connect(circle, &QPushButton::clicked, this, &PaintingProject::mySetCircle);
    connect(oval, &QPushButton::clicked, this, &PaintingProject::mySetOval);
    connect(line, &QPushButton::clicked, this, &PaintingProject::mySetLine);
    QMessageBox* messageBox = new QMessageBox(NULL);
    messageBox->addButton(circle, QMessageBox::AcceptRole);
    messageBox->addButton(oval, QMessageBox::AcceptRole);
    messageBox->addButton(line, QMessageBox::AcceptRole);
    messageBox->show();
}

void PaintingProject::loadImage()
{
    QString filePath = QFileDialog::getOpenFileName(
                    this,
                    tr("打开文件"),
                    "c:\\",
                    tr("Image (*.jpg *.png *.jpeg)")
                   );
    drawArea->loadImage(filePath);
}

void PaintingProject::loadImage(QString path)
{
    drawArea->loadImage(path);
}

void PaintingProject::loadImage(QImage* load_image)
{
    drawArea->loadImage(load_image);
}

void PaintingProject::hideToolBar()
{
    myToolbar->hide();
}

void PaintingProject::saveImage()
{
    QString filePath = QFileDialog::getSaveFileName(
                    this,
                    tr("保存文件"),
                    "c:\\",
                    tr("Image (*.jpg *.png *.jpeg)")
                    );
    drawArea->saveImage(filePath);
}

void PaintingProject::setColor()
{
    //setCursor(Qt::ArrowCursor);
    drawArea->saveChange();
    QColorDialog askForColor;
    QColor color = askForColor.getColor();
    drawArea->setColor(color);
}

void PaintingProject::myDraw()
{
    //setCursor(Qt::ArrowCursor);
    drawArea->saveChange();
    drawArea->setFunction(DRAW);
}

void PaintingProject::myDrawLine()
{
    //setCursor(Qt::ArrowCursor);
    drawArea->saveChange();
    drawArea->setFunction(LINE);
}

void PaintingProject::myDrawPoly()
{
    //setCursor(Qt::ArrowCursor);
    drawArea->saveChange();
    drawArea->setFunction(POLYGON);
}

void PaintingProject::myDrawCircle()
{
    //setCursor(Qt::ArrowCursor);
    drawArea->saveChange();
    drawArea->setFunction(CIRCLE);
}

void PaintingProject::myDrawOval()
{
    //setCursor(Qt::ArrowCursor);
    drawArea->saveChange();
    drawArea->setFunction((OVAL));
}

void PaintingProject::myDrawCurve()
{
    //setCursor(Qt::ArrowCursor);
    drawArea->saveChange();
    drawArea->setFunction((CURVE));
}

void PaintingProject::myEdit()
{
    //setCursor(Qt::ArrowCursor);
    drawArea->saveChange();
    drawArea->setFunction((BLANK));
}

void PaintingProject::myTailor()
{
    qDebug()<<"myfill!";
    //setCursor(Qt::CrossCursor);
    //drawArea->saveChange();
    drawArea->setFunction((TAILOR));
}

void PaintingProject::mySetCircle()
{
    int x = QInputDialog::getInt(NULL, tr("输入圆心x坐标"), tr("x:"));
    int y = QInputDialog::getInt(NULL, tr("输入圆心y坐标"), tr("y:"));
    int r = QInputDialog::getInt(NULL, tr("输入圆的半径"), tr("r:"));
    MyCircle circle(x, y, r);
    //drawArea->setShape(circle);
    qDebug()<<x<<y<<r;

}

void PaintingProject::mySetLine()
{
    int x1 = QInputDialog::getInt(NULL, tr("输入起点x坐标"), tr("x1:"));
    int y1 = QInputDialog::getInt(NULL, tr("输入起点y坐标"), tr("y1:"));
    int x2 = QInputDialog::getInt(NULL, tr("输入终点x坐标"), tr("x2:"));
    int y2 = QInputDialog::getInt(NULL, tr("输入终点y坐标"), tr("y2:"));
    MyLine line(x1, y1, x2, y2);
    //drawArea->setShape(line);
}

void PaintingProject::mySetOval()
{
    int x = QInputDialog::getInt(NULL, tr("输入中心x坐标"), tr("x:"));
    int y = QInputDialog::getInt(NULL, tr("输入中心y坐标"), tr("y:"));
    int a = QInputDialog::getInt(NULL, tr("输入椭圆的长轴"), tr("a:"));
    int b = QInputDialog::getInt(NULL, tr("输入椭圆的短轴"), tr("b:"));
    MyOval oval(x, y, a, b);
    //drawArea->setShape(oval);
}

void PaintingProject::myFill()
{
    drawArea->saveChange();
    drawArea->setFunction(FILL);
}

void PaintingProject::setShape(MyShape *shape)
{
    drawArea->setShape(shape);
}
