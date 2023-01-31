#ifndef CALLINGPAGE_H
#define CALLINGPAGE_H

#include <QDialog>
#include "Information.h"
#include <QTimer>
#include <QTime>
#include <QSoundEffect>

namespace Ui {
class CallPage;
}

class CallingPage : public QDialog
{
    Q_OBJECT

public:
    explicit CallingPage(QWidget *parent = nullptr);
    ~CallingPage();

private slots:
    void update();
    void getData(Information*);
    void on_cancel_clicked();

private:
    Ui::CallPage *ui;
    Information* info;
    QTimer* timer;
    QTime   time;
    QSoundEffect* effect;
    quint32 timeout;
    int random;
};

#endif // CALLINGPAGE_H
