#ifndef COST_H
#define COST_H

#define callPrice 0.1
#define messagePrice 0.2
#define trafficPrice 0.5

using namespace std;

class Cost {
public:
    Cost(int, double, double);
    void getInCalltime(double);
    void getInMessage();
    int getMessageNum();
    double getTraffic();
    double getCalltime();
    double getCallBill();
    double getMessageBill();
    double getTrafficBill();
private:
    int messageNum;
    double traffic;
    double calltime;
    const double callBill;
    const double messageBill;
    const double trafficBill;
};

#endif // COST_H
