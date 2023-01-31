#ifndef SMSPAGE_H
#define SMSPAGE_H

#include <QMainWindow>
#include "Information.h"
#include <QCloseEvent>

namespace Ui {
class SMSPage;
}

class SMSPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit SMSPage(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent*);
    ~SMSPage();

private slots:
    void getData(Information*);
    void on_sendButton_clicked();

private:
    Ui::SMSPage *ui;
    Information* info;

signals:
    void sendData(Information*);
};

#endif // SMSPAGE_H
