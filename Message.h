#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

using namespace std;

class Message {
public:
    Message(string, string, string);
    string getSendNum();
    string getSendName();
    string getMessageContent();
private:
    string sendNum;
    string sendName;
    string messageContent;
    static int count;
};

#endif // MESSAGE_H
