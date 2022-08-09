#include "MainWindow.h"
#include "Widget3D.h"
#include <QHBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(QRect(0, 0, 900, 700));

    QWidget* mainWidget = new QWidget(this);
    mainWidget->setFixedSize(QSize(800,600));
    mainWidget->move(50,50);
    mainWidget->setStyleSheet("border:1px solid black;");

    m_zoomInBtn = new QPushButton("ZoomIn",mainWidget);
    m_zoomInBtn->setStyleSheet("border:1px solid black;");
    m_zoomInBtn->setFixedSize(QSize(80,30));

    m_zoomOutBtn = new QPushButton("ZoomOut",mainWidget);
    m_zoomOutBtn->setStyleSheet("border:1px solid black;");
    m_zoomOutBtn->setFixedSize(QSize(80,30));

    m_resetBtn = new QPushButton("Reset",mainWidget);
    m_resetBtn->setStyleSheet("border:1px solid black;");
    m_resetBtn->setFixedSize(QSize(80,30));

// ---------------------------------- 3D SCENE ------------------------------------------

    Widget3D* container3d = new Widget3D(QSize(800,550), QPoint(0,50), mainWidget);

    connect(m_zoomInBtn, &QPushButton::clicked, this, [container3d](){container3d->zoomIn();});
    connect(m_zoomOutBtn, &QPushButton::clicked, this, [container3d](){container3d->zoomOut();});
    connect(m_resetBtn, &QPushButton::clicked, this, [container3d](){container3d->reset();});

    container3d->loadMesh("qrc:/test.obj");
    //container3d->loadMesh("qrc:/ship.obj");

// ------------------------------> Placements  -----------------------------------
    //zoomIn->raise();

    m_zoomInBtn->move(10,10);
    m_zoomOutBtn->move(100,10);
    m_resetBtn->move(190,10);
    container3d->move(0,50);
}


MainWindow::~MainWindow()
{
}

