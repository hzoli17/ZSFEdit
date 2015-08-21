#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QDialog>

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0);

signals:

public slots:
    void outputChanged(int index);
};

#endif // SETTINGS_H
