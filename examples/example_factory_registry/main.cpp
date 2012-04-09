#include<iostream>
#include"mili/mili.h"
#include"Speaker.h"


using namespace std;

mili::FactoryRegistry<Speaker, std::string>* mili::FactoryRegistry<Speaker, std::string>::instance;
int main()
{
    string className;
    Speaker* speaker;

    std::cout << "Which speaker would you like?" << endl;
    std::cin >> className;
    speaker = mili::FactoryRegistry<Speaker, std::string>::new_class(className);
    speaker->saySomething();
    delete speaker;
    return 0;
}
