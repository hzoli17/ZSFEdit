#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QIcon>
#include <QToolBar>
#include <QAction>
#include <QLCDNumber>
#include <QLabel>
#include <QSlider>
#include <QMessageBox>
#include <QFileDialog>
#include <QFrame>
#include "audio.h"
#include <cstdlib>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
 QMenu *file;
 QAction *newa = new QAction(tr("&New"), this);
 QAction *open = new QAction(tr("&Open"), this);
 QAction *save = new QAction(tr("&Save"), this);
 QAction *saveas = new QAction(tr("&Save as"), this);
 QAction *import = new QAction(tr("&Import sample"), this);
 QAction *quit = new QAction(tr("&Quit"), this);
 QAction *play = new QAction(tr("&Play"), this);
 QAction *stop = new QAction(tr("&Stop"), this);
 QAction *pause = new QAction(tr("&Pause"), this);
 QAction *record= new QAction(tr("&Record"), this);
 QAction *zoomin  = new QAction(tr("Zoom in"), this);
 QAction *zoomout = new QAction(tr("Zoom out"), this);
 QToolBar *toolbar = addToolBar("Main ToolBar");
 QLCDNumber *lcd = new QLCDNumber();
 QLabel * play_v = new QLabel(), * rec_v = new QLabel();
 QSlider * play_slider = new QSlider(Qt::Horizontal), * rec_slider = new QSlider(Qt::Horizontal);
 wave = new Wave();
 fileName = "";
 changed = false;
 newa->setIcon(QIcon::fromTheme("document-new"));
 newa->setShortcut(tr("CTRL+N"));
 open->setIcon(QIcon::fromTheme("document-open"));
 open->setShortcut(tr("CTRL+O"));
 save->setIcon(QIcon::fromTheme("document-save"));
 save->setShortcut(tr("CTRL+S"));
 saveas->setIcon(QIcon::fromTheme("document-save-as"));
 import->setIcon(QIcon::fromTheme("audio-x-generic"));
 zoomin->setIcon(QIcon::fromTheme("zoom-in"));
 zoomin->setShortcut(tr("CTRL+Up"));
 zoomout->setIcon(QIcon::fromTheme("zoom-out"));
 zoomout->setShortcut(tr("CTRL+Down"));
 play->setIcon(QIcon::fromTheme("media-playback-start"));
 play->setShortcut(tr("Space"));
 play->setCheckable(true);
 stop->setIcon(QIcon::fromTheme("media-playback-stop"));
 pause->setIcon(QIcon::fromTheme("media-playback-pause"));
 record->setIcon(QIcon::fromTheme("media-record"));
 record->setShortcut(tr("Ctrl+Space"));
 record->setCheckable(true);
 quit->setIcon(QIcon::fromTheme("application-exit"));
 quit->setShortcut(tr("CTRL+Q"));
 lcd->setDigitCount(8);
 lcd->display("00:00:00");
 lcd->setStyleSheet("background: black; color: #00FF00");
 lcd->setFixedSize(100, 30);
 play_v->setText(tr("Playback volume:"));
 rec_v->setText(tr("Record volume:"));
 play_slider->setMaximumWidth(50);
 play_slider->setRange(0, 100);
 rec_slider->setMaximumWidth(50);
 rec_slider->setRange(0, 100);
 file = menuBar()->addMenu("&File");
 file->addAction(newa);
 file->addAction(open);
 file->addAction(save);
 file->addAction(saveas);
 file->addSeparator();
 file->addAction(import);
 file->addSeparator();
 file->addAction(quit);
 toolbar->addAction(newa);
 toolbar->addAction(open);
 toolbar->addAction(save);
 toolbar->addSeparator();
 toolbar->addAction(import);
 toolbar->addAction(zoomin);
 toolbar->addAction(zoomout);
 toolbar->addSeparator();
 toolbar->addAction(stop);
 toolbar->addAction(pause);
 toolbar->addAction(play);
 toolbar->addAction(record);
 toolbar->addSeparator();
 toolbar->addWidget(play_v);
 toolbar->addWidget(play_slider);
 toolbar->addWidget(rec_v);
 toolbar->addWidget(rec_slider);
 toolbar->addWidget(lcd);
 connect(newa, SIGNAL(triggered()), this, SLOT(newFile()));
 connect(open, SIGNAL(triggered()), this, SLOT(openFile()));
 connect(save, SIGNAL(triggered()), this, SLOT(saveFile()));
 connect(saveas, SIGNAL(triggered()), this, SLOT(saveFileAs()));
 connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

 connect(zoomin, SIGNAL(triggered()), this, SLOT(zoomIn()));
 connect(zoomout, SIGNAL(triggered()), this, SLOT(zoomOut()));
 setCentralWidget(wave);
 float * buffer;
 buffer = (float*)malloc(44100*sizeof(float));
 for (unsigned int i=0;i<44100;i++)
 {
    buffer[i]=sin(1*(2*M_PI)*i/44100);
 }
 wave->setSampleRate(44100);
 wave->setBytesPerSecond(1000);
 wave->setBuffer(buffer, 44100);
}

void MainWindow::newFile()
{
    if (changed)
    {
        QString filename;
        if (fileName!="") filename=fileName; else filename=tr("Untitled");
        QMessageBox::StandardButton reply = QMessageBox::warning(this, tr("ZSFEdit"), tr("Save changes to ")+filename+"?", QMessageBox::Cancel|QMessageBox::No|QMessageBox::Yes);
        switch ((int)reply)
        {
            case QMessageBox::Yes:
            saveFile();
            break;
        case QMessageBox::Cancel:
            return;
            break;
        }
    }
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open path"), QDir::currentPath(), tr("ZSF Samples (*.zpw)\nAll files (*.*)"));
    if (filename!="")
    {
        newFile();
    }
}

void MainWindow::saveFile()
{
    if (fileName == "")
    {
        saveFileAs();
        return;
    }
}

void MainWindow::saveFileAs()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save path"), QDir::currentPath(), tr("ZSF Samples (*.zpw)\nAll files (*.*)"));
    if (filename!="")
    {
        fileName = filename;
        saveFile();
    }
}

void MainWindow::zoomIn()
{
    if (wave->getBytesPerSecond()+10<1500) wave->setBytesPerSecond(wave->getBytesPerSecond()+10);
}

void MainWindow::zoomOut()
{
    if (wave->getBytesPerSecond()-10>100) wave->setBytesPerSecond(wave->getBytesPerSecond()-10);
}
