#-------------------------------------------------
#
# Project created by QtCreator 2018-10-07T23:26:55
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += opengl

TARGET = Homework
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS += -lopengl32\
         -lGLU32\
           -lglut\
            -lOpengl32
LIBS += -lglut32\
        -lOpengl32

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    paintingproject.cpp \
    drawingarea.cpp \
    myshape.cpp \
    myline.cpp \
    mycircle.cpp \
    myoval.cpp \
    mypolygon.cpp \
    mycurve.cpp \
    myglwidget.cpp

HEADERS += \
        mainwindow.h \
    paintingproject.h \
    drawingarea.h \
    function.h \
    myshape.h \
    myline.h \
    mycircle.h \
    myoval.h \
    mypolygon.h \
    mycurve.h \
    myglwidget.h

FORMS += \
        mainwindow.ui \
    paintingproject.ui \
    drawingarea.ui

RESOURCES += \
    resource.qrc
