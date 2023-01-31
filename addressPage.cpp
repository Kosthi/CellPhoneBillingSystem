#include "addressPage.h"
#include "ui_addressPage.h"
#include "addContact.h"
#include "ui_addContact.h"
#include "modifyContact.h"
#include "findPage.h"
#include "ui_findPage.h"

AddressPage::AddressPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddressPage)
{
    // setupUi(this)是由.ui文件生成的类的构造函数，作用是对界面进行初始化，
    // 它按照Qt设计器里设计的样子把窗体画出来，把Qt设计器里面定义的信号和槽建立起来。
    // 也可以说，setupUi是界面和写程序之间的桥梁。
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/address.png"));
    //
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    addContact = new AddContact;
    connect(this, SIGNAL(sendData(Information*)), addContact, SLOT(getData(Information*)));
    connect(addContact, SIGNAL(sendData(int, int)), this, SLOT(getData(int, int)));
    connect(addContact, SIGNAL(sendData(Information*)), this, SLOT(getData(Information*)));
    modifyContact = new ModifyContact;
    connect(this, SIGNAL(sendData(Information*, int)), modifyContact, SLOT(getData(Information*, int)));
    connect(modifyContact, SIGNAL(sendData(Information*)), this, SLOT(getData(Information*)));
    findPage = new FindPage;
    connect(this, SIGNAL(sendData(Information*)), findPage, SLOT(getData(Information*)));
    connect(this, SIGNAL(sendData(int)), findPage, SLOT(getData(int)));
    connect(findPage, SIGNAL(sendData(int)), this, SLOT(getData(int)));
}

AddressPage::~AddressPage()
{
    delete ui;
    delete addContact;
    delete modifyContact;
    delete findPage;
}

void AddressPage::on_add_clicked()
{
    addContact->show();
    emit sendData(info);
}

// 查找联系人信号
void AddressPage::getData(int index)
{
    ui->tableView->selectRow(index);
}

// 增加联系人信号
void AddressPage::getData(int signal, int tmp)
{
    // 调用刷新模糊搜索
    findPage->fuzzySearch();
}

void AddressPage::getData(Information* info)
{
    //qDebug() << "addressPage get data!";
    this->info = info;
    ui->tableView->setModel(info->qModelAddress);
    // 调用刷新模糊搜索
    //emit sendData(1);
    emit sendData(info);
}

void AddressPage::on_delete_2_clicked()
{
    // 仅联系人被选中
    int index = ui->tableView->currentIndex().row();
    //qDebug() << index;
    if (index != -1)
    {
        info->deleteContact(index);
        findPage->fuzzySearch();
    }
}

void AddressPage::on_modify_clicked()
{
    int index = ui->tableView->currentIndex().row();
    qDebug() << index;
    // 仅当有联系人且被选中
    if (index != -1)
    {
        emit sendData(info, index);
        modifyContact->show();
    }
}

void AddressPage::on_find_clicked()
{
    emit sendData(info);
    findPage->fuzzySearch();
    findPage->show();
}

QString AddressPage::setRandStr(int strLen, int option)
{
    QString upperWord = QString("ABCDEFGHIJKLMNOPQRSTUVWZYZ");
    QString lowerWord = QString("abcdefghijklmnopqrstuvwjxyz");
    QString num = QString("0123456789");
    // String初始化数量不能超过6个，故使用QStringList容器
    QStringList home;
    home << "河北" << "山西" << "辽宁" << "吉林" << "黑龙江" << "江苏" << "浙江" << "安徽" << "福建" << "江西" << "山东" << "河南"
         << "湖北" << "湖南" << "广东" << "海南" << "四川" << "贵州" << "云南" << "陕西" << "甘肃" << "青海" << "台湾" << "北京"
         << "天津" << "上海" << "重庆" << "广西" << "内蒙古" << "西藏" << "宁夏" << "新疆" << "香港" << "澳门";
    string type[] = {"家人", "爱人", "朋友", "同学", "同事", "老师"};
    QString str = QString();
    QTime t = QTime::currentTime();
    srand(t.msec() + t.second()*1000);
    // 随机给定长度大写字符串
    if (option == 1)
    {
        for(int i = 0 ; i< strLen; ++i)
        {
            int ind = rand() % upperWord.length();
            str += upperWord.at(ind);
        }
    }
    // 随机给定长度小写字符串
    else if (option == 2)
    {
        for(int i = 0 ; i< strLen; ++i)
        {
            int ind = rand() % lowerWord.length();
            str += lowerWord.at(ind);
        }
    }
    // 随机给定长度数字
    else if (option == 3)
    {
        for(int i = 0 ; i< strLen; ++i)
        {
            int ind = rand() % num.length();
            str += num.at(ind);
        }
    }
    // 随机住址
    else if (option == 4)
    {
        int ind = rand() % home.size();
        qDebug() << home.size();
        str = home.at(ind);
    }
    // 随机类型
    else if (option == 5)
    {
        int ind = rand() % type->size();
        str = QString::fromStdString(type[ind]);
    }
    return str;
}

void AddressPage::on_testButton_clicked()
{
    QTime t = QTime::currentTime();
    srand(t.msec() + t.second()*1000);
    for (int i = 0; i < 1000; ++i)
    {
    int size = rand() % 7 + 1;
    // 生成随机名字
    QString name = setRandStr(1, 1) + setRandStr(size, 2);
    // 生成随机号码
    QString num = '1' + setRandStr(10, 3);
    // 生成随机email
    size = rand() % 10 + 1;
    QString email = setRandStr(size, 2) + "@" + setRandStr(rand() % 5 + 1, 2) + ".com";
    // 生成随机生日
    QString birth = QString::number(rand() % 124 + 1900) + "年" + QString::number(rand() % 12 + 1) + "月" + QString::number(rand() % 31 + 1) + "日";
    // 生成随机住址
    QString home = setRandStr(size, 4);
    // 生成随机类型
    QString type = setRandStr(size, 5);
    info->addContact(name, num, email, home, birth, type);
    }
}
