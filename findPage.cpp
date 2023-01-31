#include "findPage.h"
#include "ui_findPage.h"
#include <QCompleter>
#include <QListView>

FindPage::FindPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPage)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/find.png"));
}

FindPage::~FindPage()
{
    delete ui;
}

void FindPage::fuzzySearch()
{
    qDebug() << "fuzzy begin from findpage";
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
// "QListView::item:selected {background-color: rgb(74, 144, 226);}"
    // 设置模糊搜索
    QCompleter *pCompleter = new QCompleter(nameList, this);
    // 只要字符串中包含字/词就能匹配
    pCompleter->setFilterMode(Qt::MatchContains);
    ui->lineEdit->setCompleter(pCompleter);
    pCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->comboBox->setCompleter(pCompleter);
    ui->lineEdit->clear();
}

void FindPage::getData(int signal)
{
    if (signal)
    {
        fuzzySearch();
    }
}

void FindPage::getData(Information* info)
{
    qDebug() << "findPage get data!";
    this->info = info;
}

void FindPage::on_comfirm_clicked()
{
    int index = ui->comboBox->currentIndex();
    qDebug() << index;
    emit sendData(index);
}

void FindPage::on_cancel_clicked()
{
    this->close();
}

void FindPage::on_comboBox_editTextChanged(const QString& text)
{
    QString name = text.mid(0, 11).replace(" ", "");
    ui->comboBox->setCurrentText(name);
}
