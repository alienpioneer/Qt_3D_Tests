#include "MainWindow.h"
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

    QPushButton* zoomOut = new QPushButton("ZoomOut",mainWidget);
    zoomOut->setStyleSheet("border:1px solid black;");

    connect(zoomIn, &QPushButton::clicked, this, &MainWindow::on_zoomIn);
    connect(zoomOut, &QPushButton::clicked, this, &MainWindow::on_zoomOut);

// ---------------------------------- 3D SCENE ------------------------------------------

    // Create the 3d window and the renderer
    Qt3DExtras::Qt3DWindow* window = new  Qt3DExtras::Qt3DWindow();

    Qt3DExtras::QForwardRenderer *forward_renderer = window->defaultFrameGraph();
    forward_renderer->setClearColor(QColor(118,118,118));

    // Create the container for the 3d window
    QWidget* window_container = QWidget::createWindowContainer(window);
    //window_container->setMinimumSize(QSize(200,100));
    //window_container->setMaximumSize(window->screen()->size());
    window_container->setParent(mainWidget);

    // Create 3d sceene root
    Qt3DCore::QEntity* root_entity = new Qt3DCore::QEntity();
    window->setRootEntity(root_entity);

    // Create 3d camera
    Qt3DRender::QCamera* m_camera = window->camera();
    m_camera->lens()->setPerspectiveProjection(45.0f,16.0f/9.0f,0.1f,1000.0f);
    m_camera->setPosition(QVector3D(0,0,20.0f));
    m_camera->setUpVector(QVector3D(0,1,0));
    m_camera->setViewCenter(QVector3D(0,0,0));

    Qt3DExtras::QFirstPersonCameraController* camController = new Qt3DExtras::QFirstPersonCameraController(root_entity);
    camController->setCamera(m_camera);

    // Create the 3d light
    Qt3DCore::QEntity* light = new Qt3DCore::QEntity(root_entity);
    Qt3DRender::QPointLight* pointLight = new Qt3DRender::QPointLight();
    pointLight->setColor(QColor(255,255,255));
    pointLight->setIntensity(1);
    light->addComponent(pointLight);

    Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform();
    lightTransform->setTranslation(m_camera->position());
    light->addComponent(lightTransform);

    // Create the 3d object container (entity)
    Qt3DCore::QEntity* object3d = new  Qt3DCore::QEntity(root_entity);

    //----> 3d shapes
    Qt3DRender::QMesh* objMesh = new Qt3DRender::QMesh(object3d);
    objMesh->setSource(QUrl(QStringLiteral(":/Qt_logo.obj")));

    Qt3DExtras::QSphereMesh* sphereMesh = new Qt3DExtras::QSphereMesh();
    sphereMesh->setRings(30);
    sphereMesh->setSlices(30);
    sphereMesh->setRadius(3);

    Qt3DExtras::QCylinderMesh* cylinderMesh = new Qt3DExtras::QCylinderMesh();
    cylinderMesh->setLength(5);
    cylinderMesh->setRadius(3);
    cylinderMesh->setSlices(30);

    object3d->addComponent(cylinderMesh);

    // Create 3d materials
    Qt3DExtras::QPhongMaterial* phongMat = new Qt3DExtras::QPhongMaterial();
    phongMat->setDiffuse(QColor("red"));

    object3d->addComponent(phongMat);

// ------------------------------> Placements  -----------------------------------
    zoomIn->raise();
    zoomOut->raise();

    zoomIn->setFixedSize(QSize(80,30));
    zoomOut->setFixedSize(QSize(80,30));
    zoomIn->move(10,10);
    zoomOut->move(120,10);

    window_container->setFixedSize(QSize(800,550));
    window_container->move(0,50);

    //mainWidget->layout()->addWidget(window_container);
    //mainWidget->layout()->addWidget(zoomIn);
    //window_container->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_zoomIn()
{
    qDebug() << "Zoom in";
    QVector3D pos = m_camera->position();
    m_camera->setPosition(pos + QVector3D(0,0,10.0f));
}

void MainWindow::on_zoomOut()
{
    qDebug() << "Zoom out";
    QVector3D pos = m_camera->position();
    m_camera->setPosition(pos - QVector3D(0,0,10.0f));
}

