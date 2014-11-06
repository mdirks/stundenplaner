#ifndef TESTSTUNDENPLANTEMPLATEEINTRAG_H
#define TESTSTUNDENPLANTEMPLATEEINTRAG_H


#include "testcase.h"
#include "datamodel/stundenplantemplateeintrag.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class TestStundenplanTemplateEintrag : public TestCase {
public:
    TestStundenplanTemplateEintrag();
    ~TestStundenplanTemplateEintrag();
	
    void run();
    QString getName(){return QString("StundenplanTemplateEintrag");};
};

#endif
