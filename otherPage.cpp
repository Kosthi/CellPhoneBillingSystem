#include "otherPage.h"
#include "QtCore/qobjectdefs.h"
#include "ui_otherPage.h"
#include "costMapPage.h"
#include "ui_costMapPage.h"
#include "Information.h"
#include "smsPage.h"
#include "ui_smsPage.h"
#include "addressPage.h"
#include "ui_addressPage.h"
#include "callPage.h"
#include "ui_findPage.h"
#include <QCloseEvent>
#include <QTextStream>
#include <QFile>

otherPage::otherPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::otherPage)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/menu.png"));
    costPage = new CostMapPage;
    connect(this, SIGNAL(sendData(Information*)), costPage, SLOT(getData(Information*)));
    smsPage = new SMSPage;
    connect(this, SIGNAL(sendData(Information*)), smsPage, SLOT(getData(Information*)));
    addressPage = new AddressPage;
    connect(this, SIGNAL(sendData(Information*)), addressPage, SLOT(getData(Information*)));
    callPage = new CallPage;
    connect(this, SIGNAL(sendData(Information*)), callPage, SLOT(getData(Information*)));
    connect(this, SIGNAL(sendData(int)), callPage, SLOT(getData(int)));
}

otherPage::~otherPage()
{
    delete ui;
    delete callPage;
    delete smsPage;
    delete costPage;
    delete addressPage;
}

void otherPage::getData(Information* info)
{
    emit sendData(info);
    this->info = info;
}

void otherPage::on_sendSMSButton_clicked()
{
    smsPage->show();
}

void otherPage::on_costPageButton_clicked()
{
    emit sendData(info);
    costPage->show();
}

void otherPage::on_addressPageButton_clicked()
{
    addressPage->show();
}

void otherPage::on_callNumButton_clicked()
{
    emit sendData(1);
    callPage->show();
}

void otherPage::closeEvent(QCloseEvent* event)
{
    QApplication::beep();
    if (QMessageBox::warning(this, QStringLiteral("退出登录"), QStringLiteral("确定退出登录？"), QStringLiteral("确定"), QStringLiteral("取消")) == 0)
    {
        QFile file(QString("./cost/%1.txt").arg(info->getUserLabel()));
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append | QIODevice::Truncate))
        {
            QString messageNum = info->getMessageNum();
            QString calltime = info->getCalltime();
            QString traffic = info->getTraffic();
            QTextStream out(&file); //用文本流读取文件
            out << messageNum + '\n' << calltime + '\n' << traffic + '\n';
                    //<< calltime << endl << traffic; //endl起到换行的作用，在字符后面有换行
            file.close();
            qDebug() << "store data for cost success";
        }
        else
        {
            qDebug() << "fail to store data for cost";
        }
        emit sendData(bool(1));
        delete info;
        event->accept(); // 关闭
    }
    else
    {
        event->ignore(); // 忽略
    }
}
