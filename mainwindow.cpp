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
 QToolBar *toolbar = addToolBar("Main ToolBar");
 QLCDNumber *lcd = new QLCDNumber();
 QLabel * play_v = new QLabel(), * rec_v = new QLabel();
 QSlider * play_slider = new QSlider(Qt::Horizontal), * rec_slider = new QSlider(Qt::Horizontal);
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
}

void MainWindow::newFile()
{
    if (changed)
    {
        if (QMessageBox::question(this, tr("ZSFEdit"), tr("Already create new file?"), QMessageBox::Yes|QMessageBox::No) == QMessageBox::No) return;
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
