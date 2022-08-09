#include "MainWindow.h"
#include "Widget3D.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(QRect(0, 0, 900, 700));

    QWidget* mainWidget = new QWidget(this);
    mainWidget->setFixedSize(QSize(800,600));
    mainWidget->move(50,50);
    mainWidget->setStyleSheet("border:1px solid black;");
    //mainWidget->setLayout(new QHBoxLayout());
    //mainWidget->layout()->setMargin(0);

    QPushButton* zoomIn = new QPushButton("ZoomIn",mainWidget);
    zoomIn->setStyleSheet("border:1px solid black;");
    zoomIn->setFixedSize(QSize(80,30));

    QPushButton* zoomOut = new QPushButton("ZoomOut",mainWidget);
    zoomOut->setStyleSheet("border:1px solid black;");
    zoomOut->setFixedSize(QSize(80,30));

    QPushButton* reset = new QPushButton("Reset",mainWidget);
    reset->setStyleSheet("border:1px solid black;");
    reset->setFixedSize(QSize(80,30));

    connect(zoomIn, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(zoomOut, &QPushButton::clicked, this, &MainWindow::zoomOut);
    connect(reset, &QPushButton::clicked, this, &MainWindow::reset);

// ---------------------------------- 3D SCENE ------------------------------------------

    Widget3D* window_container = new Widget3D(QSize(800,550),QPoint(0,50), mainWidget);

// ------------------------------> Placements  -----------------------------------
    zoomIn->raise();
    zoomOut->raise();

    zoomIn->move(10,10);
    zoomOut->move(100,10);
    reset->move(190,10);
}


MainWindow::~MainWindow()
{
}

