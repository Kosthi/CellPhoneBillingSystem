#include "modifyContact.h"
#include "ui_AddContact.h"

ModifyContact::ModifyContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddContact)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/edit.png"));
}

ModifyContact::~ModifyContact()
{
    delete ui;
}

void ModifyContact::on_comfirm_clicked()
{
    QString name = ui->nameEdit->text();
    QString number = ui->numberEdit->text();
    QString email = ui->emailEdit->text();
    QString home = ui->homeEdit->text();
    // 日期从"xxxx/xx/xx"转化为"xxxx年xx月xx日"
    QDate date = ui->birthDateEdit->date();
    QString birth = QString::number(date.year()) + "年" + QString::number(date.month()) + "月" + QString::number(date.day()) + "日";
    QString type = ui->typeComboBox->currentText();
    info->modifyContact(name, number, email, home, birth, type);
    emit sendData(info);
    clearAll();
}

void ModifyContact::getData(Information* info, int index)
{
    qDebug() << "ModifyContent get data2!";
    qDebug() << index;
    QString name = info->getAddName(index);
    QString number = info->getAddNumber(index);
    QString email =  info->getAddEmail(index);
    QString home = info->getAddHome(index);
    QString birth = info->getAddBirth(index);
    QString type = info->getAddType(index);

    ui->nameEdit->setText(name);
    ui->numberEdit->setText(number);
    ui->emailEdit->setText(email);
    ui->homeEdit->setText(home);
    // 日期从"xxxx年xx月xx日"转化为"xxxx/xx/xx"并恢复
    birth.replace("年", "/");
    birth.replace("月", "/");
    birth.replace("日", "");
    QDate date = QDate::fromString(birth, "yyyy/M/d");
    ui->birthDateEdit->setDate(date);
    // 找到type的索引并恢复
    QList<QString> types = {"家人", "爱人", "朋友", "同学", "同事", "老师"};
    for (int i = 0; types.size(); ++i)
    {
        if (types[i] == type)
        {
            ui->typeComboBox->setCurrentIndex(i);
            break;
        }
    }
    this->info = info;
}

void ModifyContact::clearAll()
{ // 清空或还原内容
    ui->nameEdit->clear();
    ui->numberEdit->clear();
    ui->emailEdit->clear();
    ui->homeEdit->clear();
    QDate date = QDate::fromString("20000101", "yyyymmdd");
    ui->birthDateEdit->setDate(date);
    ui->typeComboBox->setCurrentIndex(0);
    this->close();
}

void ModifyContact::on_cancel_clicked()
{
    clearAll();
}
