#ifndef TESTSITZPLAN_H
#define TESTSITZPLAN_H

#include "testcase.h"

#include "qstring.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class TestSitzplan : public TestCase {

public:
    TestSitzplan();
    ~TestSitzplan();

    void run();
	QString getName(){return QString("Sitzplan");}	
};

#endif
