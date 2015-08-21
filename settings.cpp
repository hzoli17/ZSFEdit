#include "settings.h"
#include <QGridLayout>
#include <QLabel>
#include <QPicture>
#include <QPushButton>
#include <QComboBox>
#include <QDialogButtonBox>
#include "audio.h"
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
    qDebug()<<index;
    Audio::closeOutputDevice();
    if (!Audio::openAudioOutputDevice(index))
        qDebug()<<Audio::getOutError();
}
