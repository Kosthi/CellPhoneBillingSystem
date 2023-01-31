#include "callPage.h"
#include "ui_findPage.h"
#include <QCompleter>
#include <QListView>
#include "callingPage.h"

CallPage::CallPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPage)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/call.png"));
    qDebug() << "callPage born!";
}

CallPage::~CallPage()
{
    delete ui;
}

void CallPage::fuzzySearch()
{
    qDebug() << "fuzzy begin from callpage";
    QStringList nameList = info->getAddList();
    ui->comboBox->clear();
    ui->comboBox->addItems(nameList);
    ui->comboBox->setView(new QListView());
    ui->comboBox->setEditable(true);
    ui->comboBox->setLineEdit(ui->lineEdit);
    ui->comboBox->setMaxVisibleItems(10);//下拉列表显示item数
    ui->comboBox->view()->setStyleSheet("QListView {font-family: \"Arial\"; font-size: 13px; outline: 0px;}"
        "QListView::item {padding: 3px 0x 3px 5px; border-width: 0px;}"
        "QListView::item:selected {background-color: rgb(74, 144, 226);}");
    // 设置模糊搜索
    QCompleter *pCompleter = new QCompleter(nameList, this);
    // 只要字符串中包含字/词就能匹配
    pCompleter->setFilterMode(Qt::MatchContains);
    ui->lineEdit->setCompleter(pCompleter);
    pCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->comboBox->setCompleter(pCompleter);
    ui->lineEdit->clear();
}

void CallPage::getData(int signal)
{
    qDebug() << "fuzzySearch signal get!";
    if (signal)
    {
        fuzzySearch();
    }
}

void CallPage::getData(Information* info)
{
    qDebug() << "callPage get data!";
    this->info = info;
}

void CallPage::on_comfirm_clicked()
{
    if (ui->comboBox->currentText().isEmpty() == 0)
    {
        CallingPage* callingPage = new CallingPage;
        connect(this, SIGNAL(sendData(Information*)), callingPage, SLOT(getData(Information*)));
        emit sendData(info);
        callingPage->show();
        ui->comboBox->clear();
        this->close();
    }
}

void CallPage::on_cancel_clicked()
{
    this->close();
}

void CallPage::on_comboBox_editTextChanged(const QString& text)
{
    QString tmp = text;
    reverse(tmp.begin(), tmp.end());
    QString number = tmp.mid(0, 11);
    reverse(number.begin(), number.end());
    ui->comboBox->setCurrentText(number);
}
