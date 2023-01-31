#include "callingPage.h"
#include "ui_callPage.h"

CallingPage::CallingPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CallPage)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/calling.png"));
    effect = new QSoundEffect;
    effect->setSource(QUrl("qrc:/audio/audio/call.wav"));
    effect->setLoopCount(QSoundEffect::Infinite);
    effect->setVolume(1);
    effect->play();
    if (effect->isPlaying()) qDebug() << "playing";
    time.setHMS(0,0,0,0); //设置初始值
    timer = new QTimer(this);//创建一个定时器
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));//手动连接槽函
    timer->start(1000); // 1000ms触发1次
    ui->label->setText("拨号中ing");
    timeout = 0;
    QTime t = QTime::currentTime();
    srand(t.msec() + t.second()*1000);
    random = rand() % 60 + 1;
}

CallingPage::~CallingPage()
{
    delete ui;
    //delete timer;
    //delete effect;
}

void CallingPage::update()
{
    timeout++;
    if (timeout == random)
    {
        effect->stop();
        time.setHMS(0,0,0,0);
        ui->label->setText("通话中ing");
    }
    if (timeout >= random) ui->timerLabel->setText(time.toString("hh:mm:ss"));
    time = time.addSecs(1);
    qDebug() << timeout;
}

void CallingPage::getData(Information* info)
{
    this->info = info;
}

void CallingPage::on_cancel_clicked()
{
    timer->stop();
    if (effect->isPlaying()) effect->stop();
    QSoundEffect* ringoff = new QSoundEffect;
    ringoff->setSource(QUrl("qrc:/audio/audio/ringoff.wav"));
    ringoff->play();
    int hour = time.hour();
    int minute = time.minute();
    int second = time.second();
    double totalMinute = 60 * hour + minute + second / 60.0;
    info->getInCalltime(totalMinute);
    this->close();
}
