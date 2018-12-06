#include <iostream>
#include <string>

using std::string;

class InMsg{
public:
    InMsg(list_py lis, int offset = 0);
    int getTpe();
    int getStatus();
    int nextInt();
    float nextFloat();

private:
    string _body;
    int _ptr,
        _type,
        _status;
};

class OutMsg{
public:
    OutMsg(int type, int status);
    void addInt(int i);
    void addFloat(float f);
    string getBytes();
private:
    int _type, _status;
    list_py _params;
};

class Connection{
public:
    Connection(string ip, int port);
    void send(OutMsg msg);
};