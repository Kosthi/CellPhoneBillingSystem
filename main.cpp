/*
 * ... ...
 * 我喜欢那样的梦
 * 在梦里 一切都可以重新开始
 * 一切都可以慢慢解释
 * 心里甚至还能感觉到所有被浪费的时光
 * 竟然都能重回时的狂喜和感激
 * ... ...
 *
 *                ----席慕容《初相遇》
 */

#include "loginMainPage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginMainPage w;
    w.show();
    return a.exec();
}
