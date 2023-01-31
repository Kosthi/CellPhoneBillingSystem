#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

using namespace std;

class Address {
public:
    friend class Information;
    Address(string, string, string, string, string, string);
    string numPrint();
    string namePrint();
private:
    string name;
    string num;
    string email;
    string home;
    string birth;
    string type;
};

#endif // ADDRESS_H
