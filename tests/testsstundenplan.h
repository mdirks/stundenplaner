
#ifndef TESTSSTUNDENPLAN_H
#define TESTSSTUNDENPLAN_H

#include "testcase.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class TestSStundenplan : public TestCase {
public:
    TestSStundenplan();
    ~TestSStundenplan();

    void run();
    QString getName(){return QString("SStundenplan");}
    
};

#endif
