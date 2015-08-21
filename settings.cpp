#include "settings.h"
#include <QGridLayout>
#include <QLabel>
#include <QPicture>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QSettings>
#include <QSettings>
#include "audio.h"

QSettings * settings = new QSettings("config.ini", QSettings::IniFormat);
QString outputDevice = "", inputDevice = "";
Settings::Settings(QWidget *parent) :
    QDialog(parent)
{
    QGridLayout * layout=new QGridLayout(this);
    QLabel * label=new QLabel();
    QLabel * outDevL= new QLabel();
    QComboBox * outDevs = new QComboBox();
    this->setFixedSize(400, 500);
    label->setText(tr("Settings"));
    outDevL->setText(tr("Output audio device:"));
    layout->addWidget(label,0,1);
    layout->addWidget(outDevL, 1,0);
    layout->addWidget(outDevs, 1,1);
    for (unsigned int i=0;i<Audio::getAudioOutputCount();i++)
    {
        outDevs->addItem(Audio::getOutDeviceName(i));
    }
    connect(outDevs, SIGNAL(currentIndexChanged(int)), this, SLOT(outputChanged(int)));
}

void Settings::outputChanged(int index)
{
    Audio::closeOutputDevice();
    if (!Audio::openAudioOutputDevice(index)) QMessageBox::critical(this, tr("Hiba"), tr("Cannot open audio output device: ")+Audio::getOutError()); else
    settings->setValue("output.device", Audio::getOutDeviceName(index));
}

void config::loadParams()
{
    outputDevice = settings->value("output.device","").toString();
    inputDevice  = settings->value("input.device", "").toString();
    qDebug()<<"output.device = "<<outputDevice;
    for (unsigned int i=0;i<Audio::getAudioOutputCount();i++)
    {
        if (Audio::getOutDeviceName(i) == outputDevice) Audio::openAudioOutputDevice(i);
    }
    if (!Audio::isOutputOpen() && Audio::getAudioOutputCount())
        Audio::openAudioOutputDevice(Audio::getDefaultOutputDevice());
    for (unsigned int i=0;i<Audio::getAudioInputCount();i++)
    {
        if (Audio::getOutDeviceName(i) == inputDevice) Audio::openAudioInputDevice(i);
    }
    if (!Audio::isInputOpen() && Audio::getAudioInputCount())
        Audio::openAudioInputDevice(Audio::getDefaultInputDevice());
}
