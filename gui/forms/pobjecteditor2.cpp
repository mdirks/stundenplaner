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
#include "pobjecteditor2.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryproperty.h"
#include "stringeditor.h"
#include "textpropertyeditor.h"
#include "textpropertyviewer.h"
#include "pobjecticonview.h"
#include "dateeditor.h"
#include "pobjecttable.h"
#include "pobjectlabel.h"
#include "seatmap.h"
#include "datamodel/sitzplan.h"
#include "orm/repository/propertyaction.h"
#include "booleaneditor.h"

#include <qlayout.h>
#include <qlabel.h>
#include <qframe.h>
#include <qcolor.h>
#include <qtabwidget.h>
//#include <qvbox.h>
//#include <qscrollview.h>
#include <QScrollArea>



PObjectEditor2::PObjectEditor2(PObject *o, QWidget *parent, list<RepositoryProperty*> *properties)
    : /*QWidget(parent)*/ QScrollArea()
{
	
	this->mo = o;
	this->entry = Repository::getInstance()->getRepositoryEntry(mo);
	this->editRequestor = new EditRequestor();
	
	if(properties==0){
		properties = entry->getAllProperties(true);
	}
	if(properties){
        //QVBoxLayout *l = new QVBoxLayout(this);

		//QTabWidget *tw = new QTabWidget(this,0,QTabWidget::Top);
	        //l->addWidget(tw);
 
        //QScrollArea* sv = new QScrollArea(this);
        //l->addWidget(sv);
        	//QVBox* big_box = new QVBox(sv->viewport());
        	
        QWidget *mainTab = new QWidget(); //new QWidget(sv->viewport());
        //sv->setResizePolicy(QScrollView::AutoOneFit);
		//tw->addTab(mainTab,"Allgemein");
        QVBoxLayout *layout = new QVBoxLayout();
        mainTab->setLayout(layout);
		layout -> setMargin(20);

		list<RepositoryProperty*> *list_po_prop = new list<RepositoryProperty*>();

		for(list<RepositoryProperty*>::iterator it=properties->begin(); it != properties->end(); it++){
			RepositoryProperty *prop = (*it);
            QLabel *lab=new QLabel(prop->getName().c_str(),mainTab);
            layout -> addWidget(lab);
            lab->show();
            //QFrame *w=0;
            QWidget *w=0;
			if(prop->isString()){
					w= new StringEditor(mo,prop,mainTab);
                    //w->setLineWidth(0);
					layout -> addWidget( w );
			} else if(prop->isText()){
					//w =  new TextPropertyEditor(mo,prop,mainTab);
					w = new TextPropertyViewer(mo,prop,mainTab);
					w->setMinimumHeight(500);
                    //w->setLineWidth(0);
					layout -> addWidget( w ,80);

                    //w->setPaletteBackgroundColor(QColor(220,220,250));
			} else if(prop->isCollection()){
                    QWidget *collectionWidget = new QWidget(mainTab);
                    QGridLayout *collectionLayout = new QGridLayout(collectionWidget);

                    PObjectTable *table = new PObjectTable(prop,mo,this);
					table->load();
					w=table;
                    //table->setLineWidth(0);
                    //layout -> addWidget(w);

                    list<PropertyAction*> *actionList = prop->getAllActions();
					if(actionList){
						for(list<PropertyAction*>::iterator it = actionList->begin(); it != actionList->end(); it++){
							PropertyAction *pa = (*it);
							pa->setParentObject(mo);
                            QPushButton *b = new QPushButton(pa->getName().c_str(),collectionWidget);
							collectionLayout->addWidget(b,1,0);
							connect(b,SIGNAL(clicked()),pa,SLOT(perform()));
						}
					}

					collectionLayout->addWidget(table,0,0);

					PObjectIconView *iconView = new PObjectIconView(prop,mo,collectionWidget);
					iconView->load();
					//iconView -> load(prop->asCollection( mo ) );
					w = iconView;
                    iconView->setLineWidth(0);
                    collectionLayout->addWidget(w,0,0);

					layout -> addWidget( collectionWidget );


                    if(prop->getName() == "Eintraege" || prop->getName() == "Schueler"|| prop->getName() == "Fehlzeiten" || prop->getName() == "Fehlzeitmeldungen" || prop->getName() == "Noten" || prop->getName() == "Stundenbewertungen" || prop->getName() == "Bewertungen"){
						iconView->hide();
						table->show();
					} else {
						table->hide();
						iconView->show();
                    }
                    /*
                    table->hide();
                    iconView->show();
                    */
			} else if(prop->isDate()){
					layout->addWidget( new DateEditor(mo,prop,mainTab) );
			} else if(prop->isPObject()){
					if(prop->getName() == "Nonsens" /*Sitzplan*/){
						sitzplan *sp = (sitzplan*) prop->asPObject(mo);
						/*
						int r = sp->getReihen();
						int s = sp->getSpalten();
						qDebug(QString("SEATMAP (%1,%2)").arg(r).arg(s));
						*/
						//SeatMap *seatMap = new SeatMap(sp->getReihen(),sp->getSpalten(),mainTab);
						SeatMap *seatMap = new SeatMap(sp,mainTab);
						seatMap ->setMinimumHeight(500);
						layout->addWidget(seatMap);
					} else {
						list_po_prop->push_back(prop);
						/*
						PObjectLabel *olabel= new PObjectLabel(prop,mo,mainTab);
						//connect(olabel->editRequestor,SIGNAL(editRequested(PObject*)),this->editRequestor,SLOT(requestEdit(PObject*)));
						//connect(olabel->editRequestor,SIGNAL(dialogRequested(PObject*)),this->editRequestor,SLOT(requestDialog(PObject*)));
						layout->addWidget( olabel );
						*/
					}
			} else if(prop->isNumeric()){
					w= new StringEditor(mo,prop,mainTab);
                    //w->setLineWidth(0);
					layout -> addWidget( w );
			} else if(prop->isBoolean()){
					;
					layout -> addWidget(new BooleanEditor(mo,prop,mainTab));
			}
			/*
			else if(prop->isFile()){
					layout->addWidget( new FileEditor(mo,prop,mainTab));
			}
			*/

            //if(w){	 w->setFrameStyle( QFrame::Box | QFrame::Plain ); }
			
			
		}
		list<RepositoryProperty*>::iterator it = list_po_prop->begin();
			while(it != list_po_prop->end()){
				QWidget* dw = new QWidget(mainTab);
                QGridLayout *l = new QGridLayout(dw);

                l -> addWidget(new QLabel(QString::fromStdString((*it)->getName()),dw),1,1);
				PObjectLabel *olabel= new PObjectLabel(*it,mo,dw);
				
				l->addWidget( olabel, 1,2);
		
				it++;
				if(it != list_po_prop->end()){
                    l -> addWidget(new QLabel(QString::fromStdString((*it)->getName()),dw),1,3);
					PObjectLabel *olabel= new PObjectLabel(*it,mo,dw);
					l->addWidget( olabel, 1,4 );
					it++;
				}
				layout->addWidget(dw);
			}
			
			
            //setPaletteForegroundColor(QColor(150,150,170));
			
				 
			layout->addSpacing(20);
// 		if(entry->getClassName() == "klasse"){
// 			
// 		}
        setWidget(mainTab);

		
	}

}


PObjectEditor2::~PObjectEditor2()
{
}


