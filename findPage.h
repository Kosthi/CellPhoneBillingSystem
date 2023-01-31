#ifndef FINDPAGE_H
#define FINDPAGE_H

#include <QDialog>
#include "Information.h"

namespace Ui {
class FindPage;
}

class FindPage : public QDialog
{
    Q_OBJECT

public:
    explicit FindPage(QWidget *parent = nullptr);
    ~FindPage();
    void fuzzySearch();

private:
    Ui::FindPage *ui;
    Information* info;

private slots:
    void getData(Information*);
    void getData(int);
    void on_comfirm_clicked();
    void on_cancel_clicked();
    void on_comboBox_editTextChanged(const QString&);

signals:
    void sendData(int);
};

#endif // FINDPAGE_H
