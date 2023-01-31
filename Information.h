#ifndef INFORMATION_H
#define INFORMATION_H

#include "Cost.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

using namespace std;

class Information {
public:
    Information(QString, QString);
// 短信发送
    void sendSms(QString, QString, QString, QString);
// 通话时长记录
    void getInCalltime(double);
// 返回实时账单
    QString getTraffic();
    QString getTrafficCost();
    QString getCalltime();
    QString getCallCost();
    QString getMessageNum();
    QString getMessageCost();
    QString getSumCost();
// 通讯录增删改操作
    void addContact(QString, QString, QString, QString, QString, QString);
    void deleteContact(int);
    void modifyContact(QString, QString, QString, QString, QString, QString);
// 返回登录用户信息
    QString getUserName();
    QString getUserNumber();
    QString getUserLabel();
// 根据索引获取对于联系人信息
    QString getAddName(int);
    QString getAddNumber(int);
    QString getAddEmail(int);
    QString getAddHome(int);
    QString getAddBirth(int);
    QString getAddType(int);
// 处理联系人信息
    QStringList getAddList();
// 执行数据库语句
    QSqlQueryModel* qModelSMS;
    QSqlQueryModel* qModelAddress;
private:
// 账单
    Cost* cost;
// 用户信息
    QString userNumber;
    QString userName;
    QString userLabel;
// 执行数据库语句
    QSqlQuery    queryAddress;
    QSqlQuery    querySMS;
// 数据库对象 存储信息和联系人
    QSqlDatabase dbSMS;
    QSqlDatabase dbAddress;
};

#endif // INFORMATION_H
