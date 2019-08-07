
#include "testcase.h"
#include "testrunner.h"

TestCase::TestCase()
{
	this->runner = 0;
	this->observer=0;
}


TestCase::~TestCase()
{
}

void TestCase::publish(QString mes)
{
	if(observer){
		observer->message(mes);
	}
}

void TestCase::fail(QString mes)
{
	publish(QString("FAILED: ").append(mes));
	
}

void TestCase::setObserver(TestObserver *os)
{
	this->observer = os;
}

void TestCase::setRunner(TestRunner *r)
{
	this->runner = r;
}