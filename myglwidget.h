#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <glut.h>
#include <GL/glu.h>
#include <QKeyEvent>
#include<windows.h>

#include <vector>
using namespace std;

struct Vertex
{
    double x;
    double y;
    double z;
    Vertex(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Plane
{
    int x;
    int y;
    int z;
    Plane(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

protected:
    //对3个纯虚函数的重定义
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);


private:
    bool fullscreen;                                //是否全屏显示
    GLfloat m_rtri;
    GLfloat m_rquad;
    GLfloat m_scale;
    QString file;
    vector<Vertex> vertexs;
    vector<Plane> planes;
    bool load(QString f);
};


#endif // MYGLWIDGET_H
