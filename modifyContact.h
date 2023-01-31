#ifndef MODIFYCONTACT_H
#define MODIFYCONTACT_H

#include <QDialog>
#include "Information.h"
#include <QListWidget>

namespace Ui {
class AddContact;
}

class ModifyContact : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyContact(QWidget *parent = nullptr);
    ~ModifyContact();

private slots:
    void on_comfirm_clicked();
    void getData(Information*, int);
    void clearAll();
    void on_cancel_clicked();

private:
    Ui::AddContact *ui;
    Information* info;

signals:
    void sendData(Information*);
};

#endif // MODIFYCONTACT_H
