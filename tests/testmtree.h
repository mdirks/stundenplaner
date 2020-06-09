#ifndef TESTMTREE_H
#define TESTMTREE_H

#include "testcase.h"

class TestMTree : public TestCase {
public:
    TestMTree();
    ~TestMTree();

    void run();
    QString getName(){return QString("MTree");}
};

#endif // TESTMTREE_H
