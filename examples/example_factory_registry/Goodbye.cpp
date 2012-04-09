#include<iostream>
#include<cstdio>
#include"Speaker.h"
#include"mili/mili.h"

class Goodbye: public Speaker
{
    virtual void saySomething();
};

void Goodbye::saySomething()
{
    std::cout << "Goodbye" << std::endl;
}

REGISTER_FACTORIZABLE_CLASS(Speaker, Goodbye, std::string, std::string("Goodbye"));
