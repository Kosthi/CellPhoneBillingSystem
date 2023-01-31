#ifndef COSTMAPPAGE_H
#define COSTMAPPAGE_H

#include <QMainWindow>
#include "Information.h"

namespace Ui {
class CostMapPage;
}

class CostMapPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit CostMapPage(QWidget *parent = nullptr);
    ~CostMapPage();

private slots:
    void getData(Information*);

private:
    Ui::CostMapPage *ui;
    Information* info;
};

#endif // COSTMAPPAGE_H
