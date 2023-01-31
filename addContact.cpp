#include "addContact.h"
#include "ui_addContact.h"
#include <QDate>

AddContact::AddContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddContact)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/add.png"));
}

AddContact::~AddContact()
{
    delete ui;
}

void AddContact::on_comfirm_clicked()
{
    QString name = ui->nameEdit->text();
    QString num = ui->numberEdit->text();
    QString email = ui->emailEdit->text();
    QString home = ui->homeEdit->text();
    // 日期从"xxxx/xx/xx"转化为"xxxx年xx月xx日"
    QDate date = ui->birthDateEdit->date();
    QString birth = QString::number(date.year()) + "年" + QString::number(date.month()) + "月" + QString::number(date.day()) + "日";
    QString type = ui->typeComboBox->currentText();

    info->addContact(name, num, email, home, birth, type);
    //emit sendData(info);
    emit sendData(1, 1);
    clearAll();
}

void AddContact::getData(Information* info)
{
    qDebug() << "AddContact get Data!";
    this->info = info;
}

void AddContact::clearAll()
{ // 清空或还原内容
    ui->nameEdit->clear();
    ui->numberEdit->clear();
    ui->emailEdit->clear();
    ui->homeEdit->clear();
    QDateTime date = QDateTime::fromString("20000102", "yyyymmdd");
    //ui->birthDateEdit->setDateTime(QDateTime::currentDateTime());
    ui->birthDateEdit->setDateTime(date);
    ui->typeComboBox->setCurrentIndex(0);
    this->close();
}

void AddContact::on_cancel_clicked()
{
    clearAll();
}
