#ifndef TESTCASE_H
#define TESTCASE_H

#include <QString>
//#include "testrunner.h"
#include "testobserver.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class TestRunner;


class TestCase{
public:
    TestCase();
    ~TestCase();

    virtual void run()=0;
    virtual void fail(QString message);
    virtual QString getName(){return QString("Unbekannt");}
    void setObserver(TestObserver *observer);
    void setRunner(TestRunner *runner);

protected:
	void publish(QString mes);

private:
	TestRunner *runner;
	TestObserver *observer;
};

#endif
