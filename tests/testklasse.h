
#ifndef TESTKLASSE_H
#define TESTKLASSE_H

#include "testcase.h"
#include "qstring.h"
/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class TestKlasse : public TestCase {
public:
    TestKlasse();
    ~TestKlasse();

    void run();
    QString getName(){return QString("Klasse");}	
};

#endif
