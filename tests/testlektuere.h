#ifndef TESTLEKTUERE_H
#define TESTLEKTUERE_H

#include "testcase.h"

#include <QString>

class TestLektuere : public TestCase
{
public:
    TestLektuere();

    void run();
    QString getName(){return QString("Lektuere");}
};

#endif // TESTLEKTUERE_H
