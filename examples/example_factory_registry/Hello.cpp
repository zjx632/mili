#include<iostream>
#include<cstdio>
#include"Speaker.h"
#include"mili/mili.h"

class Hello: public Speaker
{
    virtual void saySomething();
};

void Hello::saySomething()
{
    std::cout << "Hello" << std::endl;
}

REGISTER_FACTORIZABLE_CLASS(Speaker, Hello, std::string, std::string("Hello"));