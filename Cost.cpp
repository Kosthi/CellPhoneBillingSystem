#include "Cost.h"

Cost::Cost(int messageNum_, double calltime_, double traffic_): callBill(callPrice), messageBill(messagePrice),
    trafficBill(trafficPrice)
{
    calltime = calltime_;
    messageNum = messageNum_;
    traffic = traffic_;
}

void Cost::getInMessage()
{
    messageNum++;
}

void Cost::getInCalltime(double time)
{
    calltime += time;
}

int Cost::getMessageNum()
{
    return messageNum;
}

double Cost::getTraffic()
{
    return traffic;
}

double Cost::getCalltime()
{
    return calltime;
}
double Cost::getCallBill()
{
    return callBill;
}

double Cost::getMessageBill()
{
    return messageBill;
}

double Cost::getTrafficBill()
{
    return trafficBill;
}
