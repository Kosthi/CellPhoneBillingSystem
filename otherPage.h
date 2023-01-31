#ifndef OTHERPAGE_H
#define OTHERPAGE_H

#include <QMainWindow>
#include "Information.h"
#include "costMapPage.h"
#include "smsPage.h"
#include "addressPage.h"
#include "callPage.h"

namespace Ui {
class otherPage;
}

class otherPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit otherPage(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent*);
    ~otherPage();

private slots:
    void getData(Information*);
    void on_sendSMSButton_clicked();
    void on_costPageButton_clicked();
    void on_addressPageButton_clicked();
    void on_callNumButton_clicked();

private:
    Ui::otherPage *ui;
    CostMapPage* costPage;
    SMSPage* smsPage;
    AddressPage* addressPage;
    CallPage* callPage;
    Information* info;

signals:
    void sendData(int);
    void sendData(bool);
    void sendData(Information*);
};

#endif // OTHERPAGE_H
