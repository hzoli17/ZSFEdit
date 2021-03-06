#include <QtGui>
#include "wave.h"

Wave::Wave(QWidget *parent)
    : QFrame(parent)
{
  m_parent = parent;
  palette.setColor(QPalette::Background, Qt::white);
  this->setAutoFillBackground(true);
  this->setPalette(palette);
  bufferSize = 0;
  sampleRate = 0;
  WaveHeight = 10;
  BytesPerSecond = 100;
  startPos = 0;
}

void Wave::paintEvent(QPaintEvent *e)
{
  QPainter qp(this);
  drawWidget(qp);

  QFrame::paintEvent(e);
}

void Wave::drawWidget(QPainter &qp)
{
    QPen pen(Qt::black, 1, Qt::SolidLine);
    QPen wavePen(Qt::blue, 1, Qt::SolidLine);
    float addVal, lastVal;
    unsigned int maxVal=150;
    qp.setPen(pen);
    qp.drawLine(0,size().height()/2, size().width(), size().height()/2);
    for (int i=0;i<size().width();i+=BytesPerSecond)
    {
    qp.drawLine(i,0, i,10);
    qp.drawText(i,20,QDateTime::fromTime_t((int)((float)i/BytesPerSecond)).toString("mm:ss"));
    }
    qp.drawLine(0,22,size().width(),22);
    if (bufferSize)
    {
        lastVal = 0;
        qp.setPen(wavePen);
        for (int i=0;i<size().width();i++)
        {
            if (bufferSize<(unsigned long)sampleRate/BytesPerSecond*(i+startPos)) break;
            addVal = ((float)maxVal/1) * audioBuffer[sampleRate/BytesPerSecond*(i+startPos)];
            if (audioBuffer[sampleRate/BytesPerSecond*i]>1.0) addVal=maxVal;
            qp.drawLine(i, size().height()/2+lastVal, i, size().height()/2 + addVal);
            lastVal = addVal;
        }
    }
}

void Wave::setBuffer(float *buffer, unsigned long bs)
{
    audioBuffer = buffer;
    bufferSize = bs;
    repaint();
}

void Wave::setSampleRate(unsigned int sr)
{
    sampleRate = sr;
}

void Wave::setBytesPerSecond(unsigned int bps)
{
    BytesPerSecond = bps;
    repaint();
}

void Wave::setPos(unsigned long pos)
{
    startPos = pos;
    repaint();
}

unsigned int Wave::getBytesPerSecond()
{
    return BytesPerSecond;
}

unsigned long Wave::getPos()
{
    return startPos;
}
