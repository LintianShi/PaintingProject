#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "myglwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton* pushButtonNewProject;
    QPushButton* pushButtonOpenFile;
    QPushButton* pushButtonClose;
    QPushButton* pushButtonGL;
    QVBoxLayout* vBoxLayout;
    QWidget* widget;
    void newProject();
    void openFile();
    void close();
    void openGL();
};

#endif // MAINWINDOW_H
