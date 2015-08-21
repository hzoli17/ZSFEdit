#include <QApplication>
#include <QWidget>
#include <QSplashScreen>
#include "RtAudio.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(800, 600);
    window.setWindowTitle("ZSF Studio");
    window.setWindowIcon(QIcon(":/ZSF.png"));
    window.show();
    window.showMaximized();
    return app.exec();
}
