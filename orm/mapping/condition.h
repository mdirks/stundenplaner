#ifndef CONDITION_H
#define CONDITION_H

#include <string>

using namespace std;

class Condition
{
public:
    Condition(string name, string value);
    ~Condition();



private:
    string name,value;
};

#endif // CONDITION_H
