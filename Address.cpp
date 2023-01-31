#include "Address.h"

Address::Address(string name_, string num_, string email_, string home_, string birth_, string type_)
{
    name = name_;
    num = num_;
    email = email_;
    home = home_;
    birth = birth_;
    type = type_;
}

string Address::numPrint()
{
    return num;
}

string Address::namePrint()
{
    return name;
}
