#ifndef TESTPCOLLECTION_H
#define TESTPCOLLECTION_H

#include "testcase.h"

class TestPCollection : public TestCase
{
public:
    TestPCollection();

    void run() override;
    QString getName() override {return QString("Test PCollection");}
};

#endif // TESTPCOLLECTION_H
