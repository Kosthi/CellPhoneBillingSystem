#include "costMapPage.h"
#include "ui_costMapPage.h"

CostMapPage::CostMapPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CostMapPage)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/cost.png"));
}

CostMapPage::~CostMapPage()
{
    delete ui;
}

void CostMapPage::getData(Information* info)
{
    ui->usedTrafficLabel->setText(info->getTraffic());
    ui->priceTrafficLabel->setText(info->getTrafficCost());
    ui->callTimeLabel->setText(info->getCalltime());
    ui->callPriceLabel->setText(info->getCallCost());
    ui->smsNumLabel->setText(info->getMessageNum());
    ui->smsPriceLabel->setText(info->getMessageCost());
    ui->totalLabel->setText(info->getSumCost());
    this->info = info;
}
