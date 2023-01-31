#include "loginMainPage.h"
#include "ui_loginMainPage.h"
#include "otherPage.h"
#include "./ui_otherPage.h"
#include "Information.h"
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDir>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

LoginMainPage::LoginMainPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginMainPage)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/login.png"));
    QDir dir;
    if (!dir.exists("./cost"))
    {
        dir.mkdir("./cost");
    }
}

LoginMainPage::~LoginMainPage()
{
    delete ui;
}

void LoginMainPage::on_comfirm_clicked()
{
    QString name = ui->name->text();
    QString number = ui->number->text();
    // 判断手机号是否合法 正则表达式判断是否都是数字
    if (number.size() != 11 || !number.contains(QRegularExpression("^\\d+$")))
    {
        QMessageBox::warning(this, "Warning", "手机号必须为11位数字");
    }
    else
    {
        info = new Information(name, number);
        otherPage* op = new otherPage;
        connect(this, SIGNAL(sendData(Information*)), op, SLOT(getData(Information*)));
        connect(op, SIGNAL(sendData(bool)), this, SLOT(getData(bool)));
        emit sendData(info);
        QMessageBox::information(this, "登录信息", "登录成功！");
        op->show();
        ui->name->clear();
        ui->number->clear();
        this->hide();
    }
}

void LoginMainPage::getData(bool signal)
{
    if (signal)
    {
        this->show();
    }
}

void LoginMainPage::closeEvent(QCloseEvent* event)
{
    if (QMessageBox::warning(this, QStringLiteral("退出"), QStringLiteral("确定退出？"), QStringLiteral("确定"), QStringLiteral("取消")) == 0)
    {
        event->accept(); // 关闭
    }
    else {
        event->ignore(); // 忽略
    }
}
