#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include "testcase.h"

#include <QMainWindow>
#include <QString>
#include <QTableWidget>
#include "testobserver.h"


#include <list>

using namespace std;

/**
	@author Marcus Dirks <m-dirks@web.de>
*/


class TestViewItem : public QTableWidgetItem, public TestObserver {
public:
    TestViewItem(TestCase *test, QTableWidget *parent);
    //TestViewItem(TestCase *test, QTableWidgetItem *parent);
	~TestViewItem(){};
	void message(QString mes);
	void run();
    QTableWidgetItem *getMessageItem();


private:
	TestCase *test;
    QTableWidgetItem *messageItem;
};


class TestView : public QTableWidget{
Q_OBJECT
public:
	TestView(QWidget *parent=0);
	~TestView();

	void setTests(list<TestCase*> *list_tests);

public slots:
	void runSelectedTests();

private:
	list<TestViewItem*> *list_items;
};





class TestRunner : public QWidget {
public:
    TestRunner(QString dbName);
    ~TestRunner();

	void testFailed(QString messages);
    static void restartDatabase();


protected:
	void init_tests();

private:
	TestView *testView;
	list<TestCase*> *listTests;

};
#endif
