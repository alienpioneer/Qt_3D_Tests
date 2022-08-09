#include "Widget3D.h"
#include <QDebug>

Widget3D::Widget3D(const QSize& size, const QPoint& position, QWidget *parent)
    : QWidget{parent},
      m_bkgColor(QColor(118,118,118))
{
    // Create the 3d window and the renderer
    Qt3DExtras::Qt3DWindow* window = new  Qt3DExtras::Qt3DWindow();

    Qt3DExtras::QForwardRenderer *forward_renderer = window->defaultFrameGraph();
    forward_renderer->setClearColor(m_bkgColor);

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
    connect(m_camera, &Qt3DRender::QCamera::positionChanged, this ,&Widget3D::on_cameraPositionChanged);

    Qt3DExtras::QOrbitCameraController* camController = new Qt3DExtras::QOrbitCameraController(m_sceneRoot);
    //Qt3DExtras::QFirstPersonCameraController* camController = new Qt3DExtras::QFirstPersonCameraController(m_sceneRoot);
    camController->setCamera(m_camera);

    // Create the 3d light
    m_lightNode = new Qt3DCore::QEntity(m_sceneRoot);
    Qt3DRender::QPointLight* pointLight = new Qt3DRender::QPointLight();
    pointLight->setColor(QColor(255,255,255));
    pointLight->setIntensity(1);
    m_lightNode->addComponent(pointLight);

    m_lightTransformNode = new Qt3DCore::QTransform();
    m_lightNode->addComponent(m_lightTransformNode);
    m_lightTransformNode->setTranslation(m_camera->position());

    // Create the 3d object container Node (entity)
    m_3dObjectNode = new  Qt3DCore::QEntity(m_sceneRoot);

    // ----> Create other 3d shapes

    Qt3DExtras::QSphereMesh* sphereMesh = new Qt3DExtras::QSphereMesh();
    sphereMesh->setRings(30);
    sphereMesh->setSlices(30);
    sphereMesh->setRadius(3);

    Qt3DExtras::QCylinderMesh* cylinderMesh = new Qt3DExtras::QCylinderMesh();
    cylinderMesh->setLength(5);
    cylinderMesh->setRadius(3);
    cylinderMesh->setSlices(30);

    //m_3dObjectNode->addComponent(cylinderMesh);
    //m_3dObjectNode->addComponent(sphereMesh);

    // ----> Create custom mesh loader
    m_objMesh = new Qt3DRender::QMesh(m_3dObjectNode);
    connect(m_objMesh, &Qt3DRender::QMesh::statusChanged, this, &Widget3D::on_meshLoaderStatusChanged);

    // Create 3d materials
    Qt3DExtras::QPhongMaterial* phongMat = new Qt3DExtras::QPhongMaterial();
    phongMat->setDiffuse(QColor("red"));

    m_3dObjectNode->addComponent(phongMat);
}


// -------------------------------------------- MESH LOADER --------------------------------------------

void Widget3D::loadMesh(const QString sourcePath)
{
    m_objMesh->setSource(QUrl(sourcePath));
    updateMeshStatus(MeshLoadingStatus::LOADING);
    //qDebug() << m_objMesh->source().toDisplayString();
}


void Widget3D::on_meshLoaderStatusChanged()
{
    if( m_objMesh->status() == Qt3DRender::QMesh::Ready )
    {
        m_3dObjectNode->addComponent(m_objMesh);
        updateMeshStatus(MeshLoadingStatus::LOADED);
    }

    //qDebug() << m_objMesh->status();
}


void Widget3D::on_cameraPositionChanged(const QVector3D &position)
{
    //qDebug() << "Camera position changed";
    //m_camera->setViewCenter(QVector3D(0,0,0));
}


void Widget3D::updateMeshStatus(const MeshLoadingStatus& status)
{
    if (status == MeshLoadingStatus::LOADING )
    {
        m_t0 = std::chrono::high_resolution_clock::now();
        qDebug() << "Mesh loading ...";
    }
    else if (status == MeshLoadingStatus::LOADED )
    {
        m_t1 = std::chrono::high_resolution_clock::now();
        qDebug() << "Mesh loaded in " << std::chrono::duration_cast<std::chrono::milliseconds>(m_t1-m_t0).count() << " ms";
    }
}


// -------------------------------------------- CAMERA CONTROLS --------------------------------------------

void Widget3D::zoomIn()
{
    m_camera->setPosition(m_camera->position() - QVector3D(0,0,10.0f));
    m_lightTransformNode->setTranslation(m_camera->position());
    //qDebug() << "Camera position " << m_camera->position();
}


void Widget3D::zoomOut()
{
    m_camera->setPosition(m_camera->position() + QVector3D(0,0,10.0f));
    m_lightTransformNode->setTranslation(m_camera->position());
    //qDebug() << "Camera position " << m_camera->position();
}


void Widget3D::reset()
{
    m_camera->setPosition(QVector3D(0,0,20.0f));
    m_camera->setViewCenter(QVector3D(0,0,0));
    m_lightTransformNode->setTranslation(m_camera->position());
    //qDebug() << "Camera position " << m_camera->position();
}
