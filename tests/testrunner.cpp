
#include "testrunner.h"
#include "teststunde.h"
#include "testlektuere.h"
#include "testsstundenplan.h"
#include "teststundenplantemplateeintrag.h"
#include "testklasse.h"
#include "testsitzplan.h"
//#include "testschueler.h"
#include "testqdatetime.h"
#include "testskalender.h"
#include "testreadcsvlistaction.h"
#include "testindirectrepositoryproperty.h"
#include "testpcollection.h"
#include "testmtree.h"

#include "orm/persistence/database.h"
#include "orm/mapping/mappingcontroler.h"
#include "datamodel/datamodelrepository.h"
#include <QApplication>
#include <QLayout>
#include <QPushButton>
#include <QString>

int main(int argc, char** argv){
    QApplication app(argc,argv);
    QCoreApplication::setApplicationName("Testrunner");
    QCoreApplication::setOrganizationName("MD");

    QString dbName=app.arguments().at(1);
    TestRunner *runner=new TestRunner(dbName);
    //a.setMainWidget(runner);

    app.exec();
}



/* ----------------------------------------------------------------------
*
*			TestRunner
*
* ----------------------------------------------------------------------*/


TestRunner::TestRunner(QString dbName) : QWidget()
{
	QBoxLayout *layout = new QVBoxLayout(this);

	testView = new TestView(this);
    testView->insertColumn(0); //Test
    testView->insertColumn(1); //Ergebnis
	layout -> addWidget(testView,10);

	QPushButton *runButton = new QPushButton("Run",this);
	layout -> addWidget(runButton,1);
	
	connect(runButton,SIGNAL(clicked()),testView,SLOT(runSelectedTests()));
	//setCentralWidget(centralWidget);
	testView->show();

    //Database::setDatabaseName(dbName);

    MappingControler::setDatabaseName(dbName);
    MappingControler::getInstance();

    //GuiConfig::getInstance()->setDatabaseName(dbName);


    DataModelRepository::getInstance();
    //GuiRepository *rp=GuiRepository::getInstance();
    //rp->initGui();

	init_tests();		
	
	show();
}

void TestRunner::restartDatabase()
{
    Database::getInstance()->close();
    MappingControler::getInstance()->close();

    MappingControler::getInstance();
    DataModelRepository::getInstance()->registerTypesWithDatabase();
}

void TestRunner::init_tests()
{
	listTests = new list<TestCase*>();

	
    listTests->push_back( new TestStunde() );
    listTests->push_back( new TestLektuere() );
    listTests->push_back( new TestQDateTime() );
    listTests->push_back( new TestPCollection() );
    listTests->push_back( new TestMTree() );

    /*
    listTests->push_back( new TestSStundenplan() );
	listTests->push_back( new TestStundenplanTemplateEintrag() );
	listTests->push_back( new TestKlasse() );
	listTests->push_back( new TestSitzplan() );
    listTests->push_back( new TestReadCsvlistAction() );
	listTests->push_back( new TestIndirectRepositoryProperty() );
	listTests->push_back( new TestSKalender() );
	listTests->push_back( new TestSchueler() );
    */

	for(list<TestCase*>::iterator it = listTests->begin(); it!= listTests->end(); it++){
		(*it)->setRunner(this);
	}

	testView->setTests(listTests);
}

void TestRunner::testFailed(QString message)
{

}

TestRunner::~TestRunner()
{
}


/* ----------------------------------------------------------------------
*
*			TestView
*
* ----------------------------------------------------------------------*/

TestView::TestView(QWidget *parent) : QTableWidget(parent)
{
	list_items = new list<TestViewItem*>();	
}

TestView::~TestView(){}

void TestView::setTests(list<TestCase*> *list_tests)
{
    int row=0;
    setRowCount(list_tests->size());
	for(list<TestCase*>::iterator it = list_tests->begin(); it != list_tests->end(); it++) {
		TestViewItem *item = new TestViewItem(*it, this);
        list_items->push_back(item);
        setItem(row,0,item);
        setItem(row,1,item->getMessageItem());
        row+=1;
	}

}

void TestView::runSelectedTests(){
	for(list<TestViewItem*>::iterator it = list_items->begin(); it != list_items->end(); it++){
		if( (*it)->isSelected()){
			(*it)->run();
			//triggerUpdate();
		}
		
	}
}

/* ----------------------------------------------------------------------
*
*			TestViewItem
*
* ----------------------------------------------------------------------*/



TestViewItem::TestViewItem(TestCase *t, QTableWidget *parent) : QTableWidgetItem(t->getName())
{
	this->test = t;
	test->setObserver(this);
    setText(t->getName());
    messageItem = new QTableWidgetItem("");
}


/*
TestViewItem::TestViewItem(TestCase *t, QTableWidgetItem *parent) : QTableWidgetItem(t->getName())
{
	this->test = t;
	test->setObserver(this);
}
*/

void TestViewItem::message(QString mes)
{
    messageItem->setText(mes);
}

void TestViewItem::run()
{
	test->run();
}

QTableWidgetItem* TestViewItem::getMessageItem()
{
    return messageItem;
}
