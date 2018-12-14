#include "myglwidget.h"
#include<GL/glu.h>
#include <QDebug>
#include <QFileDialog>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

MyGLWidget::MyGLWidget(QWidget *parent) : QGLWidget(parent)
{
    fullscreen = false;
    m_rtri = 0.0f;
    m_rquad = 0.0f;
    m_scale = 1.0f;
    setWindowState(Qt::WindowMaximized);
    file = "c:\\";
}

MyGLWidget::~MyGLWidget()
{
    ;
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    QString filePath;
    switch(event->key())
    {
    case Qt::Key_F:
        filePath = QFileDialog::getOpenFileName(
                        this,
                        tr("打开文件"),
                        file,
                        tr("off (*.off)")
                       );
        file = filePath;
        if (load(file))
        {
            paintGL();
        }
        break;
    case Qt::Key_D:
        ;
        break;
    case Qt::Key_Left:
        //qDebug()<<"left";
        m_rtri -= 1.5f;
        updateGL();
        break;
    case Qt::Key_Right:
        m_rtri += 1.5f;
        //qDebug()<<"right";
        updateGL();
        break;
    case Qt::Key_Up:
        m_rquad -= 1.5f;
        updateGL();
        break;
    case Qt::Key_Down:
        m_rquad += 1.5f;
        updateGL();
        break;
    case Qt::Key_Equal:
        m_scale *= 1.1f;
        updateGL();
        break;
    case Qt::Key_Minus:
        m_scale /= 1.1f;
        updateGL();
        break;
    }
}

bool MyGLWidget::load(QString f)
{
    vertexs.clear();
    planes.clear();
    //qDebug()<<f;
    ifstream fin;
    fin.open(f.toStdString());
    if (!fin)
    {
        return false;
    }

    string off;
    getline(fin, off);
    if (off != "OFF")
    {
        qDebug()<<QString::fromStdString(off);
        qDebug()<<"wrong";
    }
    int vertex;
    int plane;
    int line;
    fin>>vertex>>plane>>line;
    //qDebug()<<vertex<<plane<<line;
    for (int i = 0; i < vertex; i++)
    {
        double x;
        double y;
        double z;
        fin>>x>>y>>z;
        Vertex v(x, y, z);
        vertexs.push_back(v);
    }
    for (int i = 0; i < plane; i++)
    {
        int temp;
        int x;
        int y;
        int z;
        fin>>temp>>x>>y>>z;
        Plane p(x, y, z);
        planes.push_back(p);
    }
    return true;
}

void MyGLWidget::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);                   //黑色背景
        glShadeModel(GL_SMOOTH);                            //启用阴影平滑

        glClearDepth(1.0);                                  //设置深度缓存
        glEnable(GL_DEPTH_TEST);                            //启用深度测试
        glDepthFunc(GL_LEQUAL);                             //所作深度测试的类型
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正
}
void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);               //重置当前的视口
        glMatrixMode(GL_PROJECTION);                        //选择投影矩阵
        glLoadIdentity();                                   //重置投影矩阵
        //设置视口的大小
        gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
        glMatrixMode(GL_MODELVIEW);                         //选择模型观察矩阵
        glLoadIdentity();

}
void MyGLWidget::paintGL()
{
    //qDebug()<<"paint";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
        glLoadIdentity();                                   //重置当前的模型观察矩阵

        glTranslatef(0.0f, 0.0f, -6.0f);                   //左移1.5单位，并移入屏幕6.0单位
        glRotatef(m_rtri, 0.0f, 1.0f, 0.0f);
        glRotatef(m_rquad, 1.0f, 0.0f, 0.0f);
        glScalef(m_scale, m_scale, m_scale);
        for (int i = 0; i < planes.size(); i++)
        {
            //glColor3f(1.0f, 1.0f, 1.0f);
            glColor3f(0.9f, 0.9f, 0.9f);
            glBegin(GL_TRIANGLES);
            /*if (i  % 2 == 0)
            {

            }
            else
            {
                glColor3f(0.9f, 0.9f, 0.9f);
            }*/

                glVertex3f(vertexs[planes[i].x].x, vertexs[planes[i].x].y, vertexs[planes[i].x].z);
                glVertex3f(vertexs[planes[i].y].x, vertexs[planes[i].y].y, vertexs[planes[i].y].z);
                glVertex3f(vertexs[planes[i].z].x, vertexs[planes[i].z].y, vertexs[planes[i].z].z);
            glEnd();
            glColor3f(0.5f, 0.5f, 0.5f);
            glBegin(GL_LINES);
                glVertex3f(vertexs[planes[i].x].x, vertexs[planes[i].x].y, vertexs[planes[i].x].z);
                glVertex3f(vertexs[planes[i].y].x, vertexs[planes[i].y].y, vertexs[planes[i].y].z);
                glVertex3f(vertexs[planes[i].z].x, vertexs[planes[i].z].y, vertexs[planes[i].z].z);
                glVertex3f(vertexs[planes[i].x].x, vertexs[planes[i].x].y, vertexs[planes[i].x].z);
                glVertex3f(vertexs[planes[i].y].x, vertexs[planes[i].y].y, vertexs[planes[i].y].z);
                glVertex3f(vertexs[planes[i].z].x, vertexs[planes[i].z].y, vertexs[planes[i].z].z);
            glEnd();
        }
        //m_rquad += 0.5f;

        /*glLoadIdentity();                                   //重置模型观察矩阵
        glTranslatef(1.5f, 0.0f, -6.0f);                    //右移1.5单位，并移入屏幕6.0单位
        glRotatef(m_rquad, 1.0f, 0.0f, 0.0f);               //绕x轴旋转四边形
        glColor3f(0.5f, 0.5f, 1.0f);                        //一次性将当前色设置为蓝色
        glBegin(GL_QUADS);                                  //开始绘制四边形
            glVertex3f(-1.0f, 1.0f, 0.0f);                  //左上
            glVertex3f(1.0f, 1.0f, 0.0f);                   //右上
            glVertex3f(1.0f, -1.0f, 0.0f);                  //左下
            glVertex3f(-1.0f, -1.0f, 0.0f);                 //右下
        glEnd();    */                                        //四边形绘制结束

                                             //增加三角形的旋转变量


}
