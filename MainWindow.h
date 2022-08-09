#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt3DExtras>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_zoomIn();
    void on_zoomOut();

private:
    Qt3DRender::QCamera* m_camera;
};
#endif // MAINWINDOW_H
