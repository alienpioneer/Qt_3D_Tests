#include "Widget3D.h"
#include <QDebug>

Widget3D::Widget3D(const QSize& size, const QPoint& position, QWidget *parent)
    : QWidget{parent}
{
    // Create the 3d window and the renderer
    Qt3DExtras::Qt3DWindow* window = new  Qt3DExtras::Qt3DWindow();

    Qt3DExtras::QForwardRenderer *forward_renderer = window->defaultFrameGraph();
    forward_renderer->setClearColor(QColor(118,118,118));

    // Create the container for the 3d window
    QWidget* window_container = QWidget::createWindowContainer(window);
    window_container->setParent(parent);
    window_container->setFixedSize(size);
    window_container->move(position);

    // Create 3d sceene root
    m_sceneRoot = new Qt3DCore::QEntity();
    window->setRootEntity(m_sceneRoot);

    // Create 3d camera
    m_camera = window->camera();
    m_camera->lens()->setPerspectiveProjection(45.0f,16.0f/9.0f,0.1f,1000.0f);
    m_camera->setPosition(QVector3D(0,0,20.0f));
    m_camera->setUpVector(QVector3D(0,1,0));
    m_camera->setViewCenter(QVector3D(0,0,0));

    //Qt3DExtras::QOrbitCameraController* camController = new Qt3DExtras::QOrbitCameraController(m_sceneRoot);
    Qt3DExtras::QFirstPersonCameraController* camController = new Qt3DExtras::QFirstPersonCameraController(m_sceneRoot);
    camController->setCamera(m_camera);

    // Create the 3d light
    m_lightNode = new Qt3DCore::QEntity(m_sceneRoot);
    Qt3DRender::QPointLight* pointLight = new Qt3DRender::QPointLight();
    pointLight->setColor(QColor(255,255,255));
    pointLight->setIntensity(1);
    m_lightNode->addComponent(pointLight);

    Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform();
    lightTransform->setTranslation(m_camera->position());
    m_lightNode->addComponent(lightTransform);

    // Create the 3d object container (entity)
    m_3dObjectNode = new  Qt3DCore::QEntity(m_sceneRoot);

    //----> 3d shapes
    m_objMesh = new Qt3DRender::QMesh(m_3dObjectNode);
    m_objMesh->setSource(QUrl(QStringLiteral(":/testCube.obj")));

    qDebug() << m_objMesh->source().toDisplayString();

    Qt3DExtras::QSphereMesh* sphereMesh = new Qt3DExtras::QSphereMesh();
    sphereMesh->setRings(30);
    sphereMesh->setSlices(30);
    sphereMesh->setRadius(3);

    Qt3DExtras::QCylinderMesh* cylinderMesh = new Qt3DExtras::QCylinderMesh();
    cylinderMesh->setLength(5);
    cylinderMesh->setRadius(3);
    cylinderMesh->setSlices(30);

    m_3dObjectNode->addComponent(cylinderMesh);
    //object3d->addComponent(objMesh);

    // Create 3d materials
    Qt3DExtras::QPhongMaterial* phongMat = new Qt3DExtras::QPhongMaterial();
    phongMat->setDiffuse(QColor("red"));

    m_3dObjectNode->addComponent(phongMat);
}


void Widget3D::on_zoomIn()
{
    m_camera->setPosition(m_camera->position() - QVector3D(0,0,10.0f));
}

void Widget3D::on_zoomOut()
{
    m_camera->setPosition(m_camera->position() + QVector3D(0,0,10.0f));
}

void Widget3D::on_reset()
{
    m_camera->setPosition(QVector3D(0,0,20.0f));
    m_camera->setViewCenter(QVector3D(0,0,0));
}
