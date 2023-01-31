#ifndef LOGINMAINPAGE_H
#define LOGINMAINPAGE_H

#include <QMainWindow>
#include "Information.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginMainPage; }
QT_END_NAMESPACE

class LoginMainPage : public QMainWindow
{
    Q_OBJECT

public:
    LoginMainPage(QWidget *parent = nullptr);
    ~LoginMainPage();

private slots:
    void closeEvent(QCloseEvent*);
    void on_comfirm_clicked();
    void getData(bool);

private:
    Ui::LoginMainPage *ui;
    Information* info;

signals:
    void sendData(Information*);
};
#endif // LOGINMAINPAGE_H
