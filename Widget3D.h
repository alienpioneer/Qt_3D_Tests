#ifndef WIDGET3D_H
#define WIDGET3D_H

#include <Qt3DExtras>
#include <QObject>
#include <QWidget>

enum class MeshLoadingStatus
{
    LOADING = 0,
    LOADED = 1
};


class Widget3D : public QWidget
{
    Q_OBJECT
public:
    explicit Widget3D(const QSize& size, const QPoint& position, QWidget *parent = nullptr);

public:
    void zoomIn();
    void zoomOut();
    void reset();
    void loadMesh(const QString sourcePath);

private slots:
    void on_meshLoaderStatusChanged();

private:
    void updateMeshStatus(const MeshLoadingStatus& status);

private:
    Qt3DCore::QEntity*      m_sceneRoot;
    Qt3DRender::QCamera*    m_camera;
    Qt3DCore::QEntity*      m_lightNode;

    Qt3DCore::QEntity*      m_3dObjectNode;
    Qt3DRender::QMesh*      m_objMesh;

    Qt3DCore::QTransform*   m_lightTransformNode;
    QColor                  m_bkgColor;

    std::chrono::steady_clock::time_point m_t0;
    std::chrono::steady_clock::time_point m_t1;

};

#endif // WIDGET3D_H
