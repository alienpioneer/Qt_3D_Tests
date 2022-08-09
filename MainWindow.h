#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt3DExtras>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void reset();
    void zoomIn();
    void zoomOut();

private:
    QPushButton* m_zoomInBtn;
    QPushButton* m_zoomOutBtn;
    QPushButton* m_resetBtn;

};
#endif // MAINWINDOW_H
