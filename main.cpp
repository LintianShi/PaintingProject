#include "mainwindow.h"
#include <QApplication>
#include "myoval.h"
int MyOval::angle = 0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
