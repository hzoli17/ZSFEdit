#ifndef WAVE_H
#define WAVE_H
#include <QFrame>
#include <QPalette>
class Wave : public QFrame
{
Q_OBJECT
public:
    Wave(QWidget *parent =0);
protected:
    void paintEvent(QPaintEvent *e);
    void drawWidget(QPainter &qp);
private:
    QWidget *m_parent;
    QPalette palette;
};

#endif // WAVE_H
