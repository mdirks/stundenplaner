//
// C++ Implementation: pobjecteditor2
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pobjecteditor3.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryproperty.h"
#include "stringeditor.h"
#include "textpropertyeditor.h"
#include "textpropertyviewer2.h"
#include "pobjecticonview.h"
#include "dateeditor.h"
#include "pobjecttable.h"
#include "pobjectlabel.h"
#include "seatmap.h"
#include "datamodel/sitzplan.h"
#include "orm/repository/propertyaction.h"
#include "booleaneditor.h"
#include "pobjectmultiview.h"
#include "urleditor.h"

#include <qlayout.h>
#include <qlabel.h>
#include <qframe.h>
#include <qcolor.h>
#include <qtabwidget.h>
//#include <qvbox.h>
//#include <qscrollview.h>
#include <QScrollArea>
#include <QSplitter>
#include <QFormLayout>
#include <QTableWidget>
#include <QStackedWidget>



PObjectEditor3::PObjectEditor3(PObject *o, QWidget *parent, list<RepositoryProperty*> *propList)
    : QWidget(parent) /*QScrollArea()*/
{
	
	this->mo = o;
	this->entry = Repository::getInstance()->getRepositoryEntry(mo);
	this->editRequestor = new EditRequestor();



    if(propList==0){
		properties = entry->getAllProperties(true);
    } else {
        properties = propList;
    }
    if(!properties) return;


    doCommonSetup();

}


void PObjectEditor3::doCommonSetup()
{
    QSplitter *splitter = new QSplitter(this);
    mainTab = new QTabWidget(this);
    mainTab->setContentsMargins(0,0,0,0);
    mainTab->setTabPosition(QTabWidget::West);
    colTab = new QTabWidget(this);
    colTab->setContentsMargins(0,0,0,0);
    colTab->setTabPosition(QTabWidget::East);

    list<RepositoryProperty*> *list_po_prop = new list<RepositoryProperty*>();
    list<RepositoryProperty*> *list_co_prop = new list<RepositoryProperty*>();
    list<RepositoryProperty*> *list_txt_prop = new list<RepositoryProperty*>();

    QWidget *dataPane = new QWidget(this);
    QFormLayout *flayout = new QFormLayout();
    dataPane->setLayout(flayout);
    for(list<RepositoryProperty*>::iterator it=properties->begin(); it != properties->end(); it++){
            RepositoryProperty *prop = (*it);



            if(prop->isString()){
                    flayout -> addRow(prop->getName().c_str(),
                                        new StringEditor(mo,prop,mainTab));
            } else if(prop->isText()){
                    list_txt_prop->push_back(prop);
                    /*
                    w = new TextPropertyViewer(mo,prop,mainTab);
                    w->setMinimumHeight(500);
                    flayout -> addRow( prop->getName().c_str(), w );
                    */

            } else if(prop->isCollection()){
                    list_co_prop->push_back(prop);

            } else if(prop->isDate()){
                    flayout->addRow( prop->getName().c_str(),
                                       new DateEditor(mo,prop,mainTab) );
            } else if(prop->isPObject()){
                    flayout->addRow(prop->getName().c_str(),
                                   new PObjectLabel(*it,mo,this) );
                    //list_po_prop->push_back(prop);
            } else if(prop->isNumeric()){
                    flayout -> addRow(prop->getName().c_str(),
                                      new StringEditor(mo,prop,mainTab));
            } else if(prop->isBoolean()){
                    flayout -> addRow(prop->getName().c_str(),
                                        new BooleanEditor(mo,prop,mainTab));
            } else if(prop->isUrl()){
                    flayout -> addRow(prop->getName().c_str(),
                                      new UrlEditor(mo,prop,mainTab));
            }

        }
        mainTab->addTab(dataPane,"Daten");


        for(list<RepositoryProperty*>::iterator it = list_txt_prop->begin();
            it != list_txt_prop->end();it++){
            RepositoryProperty *prop = (*it);
            TextPropertyViewer2 *w = new TextPropertyViewer2(mo,prop,mainTab);
            mainTab->addTab(w,prop->getName().c_str());
            mainTab->setCurrentWidget(w);
        }

        for(list<RepositoryProperty*>::iterator it = list_co_prop->begin();
            it != list_co_prop->end();it++){
                RepositoryProperty *prop = *it;


                PObjectMultiView *multiView = new PObjectMultiView(prop,mo,this);
                multiView->load();


                colTab->addTab(multiView,(*it)->getName().c_str());

        }




        splitter->addWidget(mainTab);
        splitter->addWidget(colTab);
        splitter->setStretchFactor(0,10);

        QGridLayout *l=new QGridLayout(this);
        l->addWidget(splitter,0,0);
        //setWidget(splitter);

}

void PObjectEditor3::addTab(QWidget *w, QString title)
{
    mainTab->addTab(w,title);
    mainTab->setCurrentWidget(w);
}

/*
void PObjectEditor3::setObject(PObject *o)
{
    this->mo = o;
}
*/

PObjectEditor3::~PObjectEditor3()
{
}

void PObjectEditor3::addProperty(RepositoryProperty *rp)
{

}

void PObjectEditor3::addEditor(QWidget *w, QString title)
{
    mainTab->addTab(w,title);
}
