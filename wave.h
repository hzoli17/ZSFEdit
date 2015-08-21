#ifndef WAVE_H
#define WAVE_H
#include <QFrame>
#include <QPalette>
class Wave : public QFrame
{
Q_OBJECT
public:
    Wave(QWidget *parent =0);
    void setBuffer(float * buffer, unsigned long bs);
    void setSampleRate(unsigned int sr);
    void setBytesPerSecond(unsigned int bps);
    void setPos(unsigned long pos);
    // Get
    unsigned int getBytesPerSecond();
    unsigned long getPos();
protected:
    void paintEvent(QPaintEvent *e);
    void drawWidget(QPainter &qp);
private:
    QWidget *m_parent;
    QPalette palette;
    float * audioBuffer;
    unsigned int sampleRate;
    unsigned long bufferSize;
    unsigned int WaveHeight;
    unsigned int BytesPerSecond;
    unsigned long startPos;
};

#endif // WAVE_H
