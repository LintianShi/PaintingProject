#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintingproject.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setGeometry(500, 100, 400, 400);

    //设置界面标题栏
    setWindowTitle("My Painter");

    widget = new QWidget();
    this->setCentralWidget(widget);
    vBoxLayout = new QVBoxLayout(this);


    //设置新建项目按钮
    pushButtonNewProject = new QPushButton(this);
    vBoxLayout->addWidget(pushButtonNewProject);
    pushButtonNewProject->setText(tr("新建项目(&N)"));
    //pushButtonNewProject->setGeometry(165, 30, 80, 75);
    //pushButtonNewProject->setMaximumSize(QSize(80, 75));
    pushButtonNewProject->setStatusTip(tr("建立一个新的项目(Ctrl + N)"));
    pushButtonNewProject->setShortcut(tr("Ctrl+N"));
    connect(pushButtonNewProject, &QPushButton::clicked, this, &MainWindow::newProject);

    //设置打开文件按钮
    pushButtonOpenFile = new QPushButton(this);
    vBoxLayout->addWidget(pushButtonOpenFile);
    pushButtonOpenFile->setText(tr("打开文件(&O)"));
    //pushButtonOpenFile->setGeometry(165, 130, 80, 75);
    pushButtonOpenFile->setStatusTip(tr("打开一个图片文件(Ctrl + O)"));
    pushButtonOpenFile->setShortcut(tr("Ctrl+O"));
    connect(pushButtonOpenFile, &QPushButton::clicked, this, &MainWindow::openFile);

    pushButtonGL = new QPushButton(this);
    vBoxLayout->addWidget(pushButtonGL);
    pushButtonGL->setText(tr("三维图形(&G)"));
    //pushButtonClose->setGeometry(165, 230, 80, 75);
    pushButtonGL->setStatusTip(tr("三维图形(Ctrl + G)"));
    pushButtonGL->setShortcut(tr("Ctrl+G"));
    connect(pushButtonGL, &QPushButton::clicked, this, &MainWindow::openGL);

    //设置退出按钮
    pushButtonClose = new QPushButton(this);
    vBoxLayout->addWidget(pushButtonClose);
    pushButtonClose->setText(tr("退出(&Q)"));
    //pushButtonClose->setGeometry(165, 230, 80, 75);
    pushButtonClose->setStatusTip(tr("退出(Ctrl + Q)"));
    pushButtonClose->setShortcut(tr("Ctrl+Q"));
    connect(pushButtonClose, &QPushButton::clicked, this, &MainWindow::close);

    widget->setLayout(vBoxLayout);

}

MainWindow::~MainWindow()
{
    delete pushButtonClose;
    delete pushButtonNewProject;
    delete pushButtonOpenFile;
    delete vBoxLayout;
    delete widget;
    delete ui;
}

void MainWindow::newProject()
{
    PaintingProject* newProject = new PaintingProject();
    newProject->setWindowModality(Qt::ApplicationModal);
    newProject->show();
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(
                    this,
                    tr("打开文件"),
                    "c:\\",
                    tr("Image (*.jpg *.png *.jpeg)")
                   );
    PaintingProject* newProject = new PaintingProject();
    newProject->setWindowModality(Qt::ApplicationModal);
    newProject->show();
    newProject->loadImage(filePath);
    newProject->hideToolBar();
}

void MainWindow::close()
{
    QApplication::exit();
}

void MainWindow::openGL()
{
    MyGLWidget* w = new MyGLWidget;
    w->setWindowModality(Qt::ApplicationModal);
    w->resize(800, 600);
    w->show();

}
