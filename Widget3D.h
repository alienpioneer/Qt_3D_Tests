#ifndef WIDGET3D_H
#define WIDGET3D_H

#include <Qt3DExtras>
#include <QObject>
#include <QWidget>


class Widget3D : public QWidget
{
    Q_OBJECT
public:
    explicit Widget3D(const QSize& size, const QPoint& position, QWidget *parent = nullptr);

private slots:
    void on_zoomIn();
    void on_zoomOut();
    void on_reset();

private:
    Qt3DCore::QEntity*      m_sceneRoot;
    Qt3DRender::QCamera*    m_camera;
    Qt3DCore::QEntity*      m_lightNode;

    Qt3DCore::QEntity*      m_3dObjectNode;
    Qt3DRender::QMesh*      m_objMesh;
};

#endif // WIDGET3D_H
