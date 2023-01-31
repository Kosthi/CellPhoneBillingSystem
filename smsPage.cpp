#include "smsPage.h"
#include "ui_smsPage.h"
#include <QDebug>
#include <QSoundEffect>

SMSPage::SMSPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SMSPage)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/sms.png"));
}

SMSPage::~SMSPage()
{
    delete ui;
}

// 发送短信并刷新短信记录
void SMSPage::on_sendButton_clicked()
{
    QString receiveNumber = ui->sendNum->text();
    QString smsContent = ui->smsContent->toPlainText();
    // 判断手机号是否合法 正则表达式判断是否都是数字
    if (receiveNumber.size() != 11 || !receiveNumber.contains(QRegularExpression("^\\d+$")))
    {
        QMessageBox::warning(this, "Warning", "手机号必须为11位数字");
    }
    else
    {
    if (!smsContent.isEmpty())
    {
        qDebug() << "Send Message";
        info->sendSms(info->getUserName(), info->getUserNumber(), smsContent, receiveNumber);
    }
    QSoundEffect* effect = new QSoundEffect;
    effect->setSource(QUrl("qrc:/audio/audio/sendsms.wav"));
    effect->setVolume(1);
    effect->play();
    if (effect->isPlaying()) qDebug() << "playing";
    ui->smsContent->clear();
    }
}

void SMSPage::getData(Information* info)
{
    qDebug() << "SMSPage get date!";
    this->info = info;
    // 载入短信数据
    ui->smsTableView->setModel(info->qModelSMS);
}

void SMSPage::closeEvent(QCloseEvent* event)
{
    ui->sendNum->clear();
    event->accept();
}
