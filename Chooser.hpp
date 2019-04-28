#pragma once
#include <string>
using namespace std;
using std::string;



namespace bullpgia{
class Chooser{
    
    private:
    string _choose;
    
    public:    
        Chooser(){}
        Chooser(const string& choose){_choose= choose;}
        virtual string choose(uint length){return _choose;}
};
};