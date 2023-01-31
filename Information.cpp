#include <cmath>
#include "Information.h"
#include <QFile>
#include <QDebug>

Information::Information(QString name, QString number): userNumber(number), userName(name)
{
    dbAddress = QSqlDatabase::addDatabase("QSQLITE", "dbAddress");
    dbSMS = QSqlDatabase::addDatabase("QSQLITE", "dbSMS");
    dbSMS.setDatabaseName("dbSMS.db");
    dbAddress.setDatabaseName("dbAddress.db");
    if(dbAddress.open() && dbSMS.open())
    {
        qDebug() << "connect success!";

    }
    else
    {
        QString errInfo = dbAddress.lastError().text();
        qDebug() << "connect fail!";
        qDebug() << errInfo;
              //QMessageBox::information(this,"connection info","connect failed!"+errInfo);
    }

    queryAddress = QSqlQuery(dbAddress);
    querySMS = QSqlQuery(dbSMS);

    QStringList tableList = dbAddress.tables();
    int i;
    for (i = 0; i < tableList.size(); ++i)
    {
        QString tableName = "user" + QString::number(i);
        queryAddress.exec(QString(R"(SELECT * FROM '%1';)").arg(tableName));
        queryAddress.first();
        if (number == queryAddress.value(1).toString())
        {
            userLabel = tableName;
            if (queryAddress.value(0).toString() == "")
            {
                if (queryAddress.exec(QString("update '%1' set 姓名 = '%2' where 电话 = '%3'")
                        .arg(userLabel).arg(name).arg(number)))
                {
                    qDebug() << "update old user name!";
                }
                else
                {
                    qDebug() << queryAddress.lastError();
                }
            }
            //querySMS.exec(QString("select * from '%1'").arg(userLabel));
            //qModelAddressSMS->setQuery(querySMS);
            qDebug() << "old user login!";
            break;
        }
    }
    if (i == tableList.size())
    {
    userLabel = "user" + QString::number(tableList.size());
    QString sql = QString(R"(CREATE TABLE '%1' (
                           姓名 TEXT,
                           电话 TEXT UNIQUE NOT NULL,
                           邮箱 TEXT,
                           住址 TEXT,
                           生日 TEXT,
                           类型 TEXT
                           );)").arg(userLabel);
          //QSqlQuery构造前，需要db已打开并连接
          //未指定db或者db无效时使用默认连接进行操

    if(queryAddress.exec(sql))
    {
        qDebug()<<"init table success from dbAddress for new user";
    }
    else
    {
        //打印sql语句错误信息
        qDebug()<<"init table error from dbAddress for new user"<<queryAddress.lastError();
    }
    sql = QString(R"(CREATE TABLE '%1' (
                               发送人   TEXT,
                               电话     TEXT NOT NULL,
                               短信内容  TEXT NOT NULL
                               );)").arg(userLabel);
    querySMS.exec(sql);
    //addContact(name, number, "", "", "", "");
    queryAddress.exec(QString(R"(INSERT INTO '%1'(姓名, 电话) VALUES('%2', '%3');)")
                         .arg(userLabel).arg(name).arg(number));
    qDebug() << "init new user!" << queryAddress.lastError();
    }

    qModelAddress = new QSqlQueryModel();
    qModelSMS = new QSqlQueryModel;

    querySMS.exec(QString(R"(SELECT * FROM '%1';)").arg(userLabel));
    qModelSMS->setQuery(querySMS);
    queryAddress.exec(QString(R"(SELECT * FROM '%1';)").arg(userLabel));
    qModelAddress->setQuery(queryAddress);

    QFile file(QString("./cost/%1.txt").arg(userLabel));
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //使用QTextStream一行一行读取文件
            QTextStream in(&file);
            QString messageNum = in.readLine();
            QString calltime = in.readLine();
            QString traffic = in.readLine();
            cost = new Cost(messageNum.toInt(), calltime.toDouble(), traffic.toDouble());
            qDebug() << "load data for cost success" << userLabel;
        }
        else
        {
            qDebug() << "fail to load data for cost";
        }
    }
    else
    {
        cost = new Cost(0, 0.0, 0.0);
        qDebug() << "init data for cost";
    }
}

// 在已登录的用户寻找发送对象，并调用对象的getSms接受信息
void Information::sendSms(QString sendName, QString sendNumber, QString smsContent, QString receiveNumber)
{
    cost->getInMessage();
    QStringList tableList = dbAddress.tables();
    for (int i = 0; i < tableList.size(); ++i)
    {
        QString tableName = "user" + QString::number(i);
        queryAddress.exec(QString(R"(SELECT * FROM '%1';)").arg(tableName));
        queryAddress.first();
        if (receiveNumber == queryAddress.value(1).toString())
        {
            int ok = querySMS.exec(QString(R"(INSERT INTO '%1' VALUES('%2', '%3', '%4');)")
                                 .arg(tableName).arg(sendName).arg(sendNumber).arg(smsContent));
            //qModelAddress->setQuery(query);
            if (ok)
            {
                qDebug()<<"insert data success to SMS";
            }
            else
            {
                //打印sql语句错误信息
                qDebug()<<"insert data error to SMS"<< querySMS.lastError();
            }
            querySMS.exec(QString("select * from '%1'").arg(userLabel));
            qModelSMS->setQuery(querySMS);
            return;
        }
    }

    int userNums = dbAddress.tables().size();
    QString tableName = "user" + QString::number(userNums);
    QString sql = QString(R"(CREATE TABLE '%1' (
                               发送人   TEXT,
                               电话     TEXT NOT NULL,
                               短信内容  TEXT NOT NULL
                               );)").arg(tableName);
    querySMS.exec(sql);
    int ok = querySMS.exec(QString(R"(INSERT INTO '%1' VALUES('%2', '%3', '%4');)")
                         .arg(tableName).arg(sendName).arg(sendNumber).arg(smsContent));
    if (ok)
    {
        qDebug()<<"insert data success to SMS with creating new user";
    }
    else
    {
        //打印sql语句错误信息
        qDebug()<<"insert data error to SMS"<< querySMS.lastError();
    }

    sql = QString(R"(CREATE TABLE '%1' (
                           姓名 TEXT,
                           电话 TEXT UNIQUE NOT NULL,
                           邮箱 TEXT,
                           住址 TEXT,
                           生日 TEXT,
                           类型 TEXT
                           );)").arg(tableName);
          //QSqlQuery构造前，需要db已打开并连接
    queryAddress.exec(sql);
    ok = queryAddress.exec(QString(R"(INSERT INTO '%1' VALUES('%2', '%3', '%4', '%5', '%6', '%7');)")
                         .arg(tableName).arg("").arg(receiveNumber).arg("").arg("").arg("").arg(""));
    if (ok)
    {
        qDebug()<<"insert new table to user success";
    }
    else
    {
        //打印sql语句错误信息
        qDebug()<<"insert new table error" << queryAddress.lastError();
    }
}

// 通话时长记录
void Information::getInCalltime(double time)
{
    cost->getInCalltime(time); // 更新cost的通话时长calltime
}

// 通讯录增删改操作
void Information::addContact(QString name, QString number, QString email, QString home, QString birth, QString type)
{
    int ok = queryAddress.exec(QString(R"(INSERT INTO '%1' VALUES('%2', '%3', '%4', '%5', '%6', '%7');)")
                         .arg(userLabel).arg(name).arg(number).arg(email).arg(home).arg(birth).arg(type));
    if (ok)
    {
        qDebug()<<"insert table success";
    }
    else
    {
        // 打印sql语句错误信息
        qDebug() << "insert table error" << queryAddress.lastError();
    }
    queryAddress.exec(QString("select * from '%1'").arg(userLabel));
    qModelAddress->setQuery(queryAddress);
    // 显示全部数据
    while (qModelAddress->canFetchMore())
        qModelAddress->fetchMore();
}

void Information::deleteContact(int row)
{
    QString number = qModelAddress->data(qModelAddress->index(row, 1)).toString();
    // 电话在数据库中以unique方式存储，用其查找要删除的联系人
    if (queryAddress.exec(QString("delete from '%1' where 电话 = '%2'").arg(userLabel).arg(number)))
    {
        qDebug() << "delete ok";
    }
    else
    {
        // 打印sql语句错误信息
        qDebug() << queryAddress.lastError();
    }
    queryAddress.exec( QString("select * from '%1'").arg(userLabel));
    qModelAddress->setQuery(queryAddress);
    // 显示全部数据
    while (qModelAddress->canFetchMore())
        qModelAddress->fetchMore();
}

void Information::modifyContact(QString name, QString number, QString email, QString home, QString birth, QString type)
{
    // 电话在数据库中以unique方式存储，用其查找要删除的联系人
    if (queryAddress.exec(QString("update '%1' set 姓名 = '%2', 电话 = '%3', 邮箱 = '%4', 住址 = '%5', 生日 = '%6', 类型 = '%7' where 电话 = '%8'")
                          .arg(userLabel).arg(name).arg(number).arg(email).arg(home).arg(birth).arg(type).arg(number)))
    {
        qDebug() << "modify ok";
    }
    else
    {
        // 打印sql语句错误信息
        qDebug() << queryAddress.lastError();
    }
    queryAddress.exec(QString("select * from '%1'").arg(userLabel));
    qModelAddress->setQuery(queryAddress);
    // 显示全部数据
    while (qModelAddress->canFetchMore())
        qModelAddress->fetchMore();
}

// 处理联系人信息
QStringList Information::getAddList()
{
    queryAddress.exec(QString(R"(SELECT * FROM '%1';)").arg(userLabel));
    //获取查询结果的第01个值，
    //如果结果是多行数据，可用while(query.next()){}遍历每一行
    QStringList list;
    while (queryAddress.next())
    {
        QString name = queryAddress.value(0).toString();
        QString number = queryAddress.value(1).toString();
        list << QString("%1 %2").arg(name, -11).arg(number);
    }
    return list;
}

// 根据索引获取对于联系人信息
QString Information::getAddName(int row)
{
    QString name = qModelAddress->data(qModelAddress->index(row, 0)).toString();
    return name;
}

QString Information::getAddNumber(int row)
{
    QString number = qModelAddress->data(qModelAddress->index(row, 1)).toString();
    return number;
}

QString Information::getAddEmail(int row)
{
    QString email = qModelAddress->data(qModelAddress->index(row, 2)).toString();
    return email;
}

QString Information::getAddHome(int row)
{
    QString home = qModelAddress->data(qModelAddress->index(row, 3)).toString();
    return home;
}

QString Information::getAddBirth(int row)
{
    QString birth = qModelAddress->data(qModelAddress->index(row, 4)).toString();
    return birth;
}

QString Information::getAddType(int row)
{
    QString type = qModelAddress->data(qModelAddress->index(row, 5)).toString();
    return type;
}

// 返回实时账单
QString Information::getTraffic()
{
    return QString::number(cost->getTraffic());
}

QString Information::getTrafficCost()
{
    return QString::number(cost->getTraffic() * cost->getTrafficBill());
}

QString Information::getCalltime()
{ // 用来返回Information中cost中的calltime,返回类型为QString
    return QString::number(cost->getCalltime());
}

QString Information::getMessageNum()
{
    return QString::number(cost->getMessageNum());
}

QString Information::getCallCost()
{
    // 向上取整数
    int a = ceil(cost->getCalltime());
    return QString::number(a * cost->getCallBill());
}

QString Information::getMessageCost()
{
    return QString::number(cost->getMessageNum() * cost->getMessageBill());
}

QString Information::getSumCost()
{
    return QString::number(getMessageCost().toDouble() + getCallCost().toDouble(), 'f', 5); //将T类型转化成string返回
}

// 返回登录用户信息
QString Information::getUserName()
{
    return userName;
}

QString Information::getUserNumber()
{
    return userNumber;
}

QString Information::getUserLabel()
{
    return userLabel;
}

// 弃用代码
//template <class Type>
//Type stringToNum(const string& str)
//{ //将string转化成T类型相加，返回T类型
//    istringstream iss(str);
//    Type num;
//    iss >> num;
//    return num;
//}

//void Information::deleteContact(int index)
//{
//    QString num = add[index].numPrint();
//    QString name = add[index].namePrint();
//    for (vector<Address>::iterator it = add.begin(); it != add.end();)
//    {

//        //qDebug() << index;
//        //qDebug() << QString::fromStdString(it->namePrint()) << QString::fromStdString(name);
//        if (it->numPrint() == num && it->namePrint() == name)
//        {
//            qDebug() << "delete success";
//            // 可能存在迭代器失效
//            it = add.erase(it);
//            break;
//        }
//        else
//            it++;
//    }
//}
