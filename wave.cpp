#include <QtGui>
#include "wave.h"

Wave::Wave(QWidget *parent)
    : QFrame(parent)
{
  m_parent = parent;
  palette.setColor(QPalette::Background, Qt::white);
  this->setAutoFillBackground(true);
  this->setPalette(palette);
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
    qp.setPen(pen);
    qp.drawLine(0,size().height()/2, size().width(), size().height()/2);
}
