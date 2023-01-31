#include "Message.h"

int Message::count = 0;

Message::Message(string sendNum_, string sendName_, string messageContent_)
{
    sendNum = sendNum_;
    sendName = sendName_;
    messageContent = messageContent_;
}

string Message::getSendNum()
{
    return sendNum;
}

string Message::getSendName()
{
    return sendName;
}

string Message::getMessageContent()
{
    return messageContent;
}
