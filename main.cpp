#include <QApplication>
#include <QWidget>
#include <QSplashScreen>
#include "RtAudio.h"
#include "mainwindow.h"
#include "audio.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    QSplashScreen * splash = new QSplashScreen(QPixmap(":/ZSF.png"));
    //config::loadParams();
    window.resize(800, 600);
    window.setWindowTitle("ZSF Studio");
    window.setWindowIcon(QIcon(":/ZSF.png"));
    window.show();
    window.showMaximized();
    return app.exec();
}
