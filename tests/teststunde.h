
#ifndef TESTSTUNDE_H
#define TESTSTUNDE_H

#include "testcase.h"
#include "datamodel/stunde.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class TestStunde : public TestCase {
public:
    TestStunde();
    ~TestStunde();

    void run();
    QString getName(){return QString("TestStunde");}

private:
	stunde* testCreateObject();
};

#endif
