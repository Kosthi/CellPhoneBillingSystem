#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include <QDialog>
#include "Information.h"

namespace Ui {
class AddContact;
}

class AddContact : public QDialog
{
    Q_OBJECT

public:
    explicit AddContact(QWidget *parent = nullptr);
    ~AddContact();

private slots:
    void on_comfirm_clicked();
    void getData(Information*);
    void clearAll();
    void on_cancel_clicked();

private:
    Ui::AddContact *ui;
    Information* info;

signals:
    void sendData(int, int);
    void sendData(Information*);
};

#endif // ADDCONTACT_H
