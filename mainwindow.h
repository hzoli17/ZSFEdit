#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QApplication>
#include <QString>
#include "wave.h"
class MainWindow : public QMainWindow
{
Q_OBJECT
private:
    QString fileName;
    bool changed;
     Wave * wave ;
public:
    MainWindow(QWidget *parent = 0);
private slots:
    // Menus
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    // Zoom
    void zoomIn();
    void zoomOut();
};
#endif
