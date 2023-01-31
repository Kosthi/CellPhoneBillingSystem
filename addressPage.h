#ifndef ADDRESSPAGE_H
#define ADDRESSPAGE_H

#include <QMainWindow>
#include "QtWidgets/qlistwidget.h"
#include "addContact.h"
#include "Information.h"
#include "modifyContact.h"
#include "findPage.h"

namespace Ui {
class AddressPage;
}

class AddressPage : public QMainWindow
{
    Q_OBJECT

public:
//当传入一个非空指针parent时，表示这个新的窗口为parent所指窗口的子窗口，那么当父窗口被删除时，子窗口也会自动的被删除；
//而传入一个空指针*parent=0时，表示这个新窗口是独立的，不是任何窗口的子窗口
    explicit AddressPage(QWidget *parent = nullptr);
    QString setRandStr(int, int);
    ~AddressPage();

private slots:
    void on_add_clicked();
    void getData(int);
    void getData(int, int);
    void getData(Information*);
    void on_delete_2_clicked();
    void on_modify_clicked();
    void on_find_clicked();
    void on_testButton_clicked();

private:
    Ui::AddressPage *ui;
    // 使用一套界面ui
    AddContact* addContact;
    ModifyContact* modifyContact;
    Information* info;
    FindPage* findPage;

signals:
    void sendData(int);
    void sendData(Information*);
    void sendData(Information*, int);
};

#endif // ADDRESSPAGE_H
