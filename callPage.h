#ifndef CALLPAGE_H
#define CALLPAGE_H

#include <QDialog>
#include "Information.h"
#include "callingPage.h"

namespace Ui {
class FindPage;
}

class CallPage : public QDialog
{
    Q_OBJECT

public:
    explicit CallPage(QWidget *parent = nullptr);
    ~CallPage();
    void fuzzySearch();

private slots:
    void getData(int);
    void getData(Information*);
    void on_comfirm_clicked();
    void on_cancel_clicked();
    void on_comboBox_editTextChanged(const QString&);

private:
    Ui::FindPage *ui;
    Information* info;
    //CallingPage* callingPage;

signals:
    void sendData(Information*);
};

#endif // CALLPAGE_H
