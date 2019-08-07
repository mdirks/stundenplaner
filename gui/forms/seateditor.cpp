//
// C++ Implementation: seateditor
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "seateditor.h"
//#include <qvbox.h>
#include <QLayout>
#include <QTableWidget>
#include <QScrollArea>

#include "pobjectlabel.h"
#include "pobjecttable.h"
#include "gui/base/guiobjectfactory.h"
//#include "actions/createaction.h"
#include "gui/base/guiconfig.h"
#include "orm/transactions/transactions.h"
#include "datamodel/klasse.h"
#include "datamodel/stundenplaneintrag.h"
#include "datamodel/fehlzeitmapper.h"
#include "services/sstundenplan.h"

#include "orm/repository/repository.h"



SeatEditor::SeatEditor(platz *p, klasse *k, map<int,list<stundenplaneintrag*>* > map_eintraege, QWidget *parent)
	: QWidget(parent)
{
	pl = p;
	kl = k;
	editRequestor = new EditRequestor();
	this->map_eintraege = map_eintraege;
	if(pl!=0){
	QVBoxLayout *l = new QVBoxLayout(this);
	//NameWidget *nameWidget = new NameWidget(this);
	//l->addWidget(nameWidget);
	RepositoryProperty *rp_schueler = Repository::getInstance()->getRepositoryEntry( "platz" )->getProperty( "Schueler" );
	nameWidget = new PObjectLabel(rp_schueler, pl,this, false, false); 
	l->addWidget(nameWidget);
	nameWidget->setMaximumWidth(300);
	connect(nameWidget,SIGNAL(objectChanged()),this,SLOT(loadEintraege()));
	
	
	int nrow = map_eintraege.size();
	int ncol = map_eintraege[1]->size();

    QScrollArea* sv = new QScrollArea(this);
    stundenTable = new QTableWidget(nrow,ncol,this);
	sv->setMaximumHeight(150);
	sv->setMaximumWidth(50+45*ncol);
	for(int c=0; c<ncol; c++){
		stundenTable->setColumnWidth(c,45);
	}
    sv->setWidget(stundenTable);
    // todo: sv->setResizePolicy(QScrollView::AutoOneFit);
	
	loadEintraege();
	l->addWidget(sv);
	
	}
}

void SeatEditor::loadEintraege(){
	int row=0;
	int col=0;

	RepositoryProperty *rp_schueler = Repository::getInstance()->getRepositoryEntry( "platz" )->getProperty( "Schueler" );
	schueler *s = (schueler*) rp_schueler->asPObject(pl);
	if(s){ 
	
		for(map<int,list<stundenplaneintrag*>* >::iterator it=map_eintraege.begin(); it!=map_eintraege.end(); it++){
				list<stundenplaneintrag*> *list_eintraege = it->second;
				col=0;
				row=it->first;
				//stundenTable->setRowHeight(row,35);
				for(list<stundenplaneintrag*>::iterator itt = list_eintraege->begin(); itt!= list_eintraege->end(); itt++){
					stundenplaneintrag* e = (*itt);
					MarkWidget *markWidget = new MarkWidget(s,e,stundenTable,this);
					stundenTable->setCellWidget(row,col,markWidget);
                    qDebug() << QString("->inserted into %1,%2").arg(row).arg(col);
					//stundenTable->setColumnWidth(col,35);
					++col;
				}
		}
		
			
	}else {
        for(int r = 0; r < stundenTable->rowCount(); r++){
            for(int c=0; c<stundenTable->columnCount(); c++){
                stundenTable->takeItem(r,c);
			}
		}
	}
}

SeatEditor::~SeatEditor()
{
}


schueler* SeatEditor::getSchueler()
{
	if(pl){
		return pl->getSchueler();
	} else {
		qDebug("SeatEditor: no platz set, cannot return schuerl");
		return 0;
	}
}

/*
void SeatEditor::setSchueler(schueler *s){
	//this->m_s = s;
	this->pl->setSchueler(s);
	nameWidget->setObject(s);
}
*/


NameWidget::NameWidget(QWidget *parent)
	: QWidget(parent)
{
	
	QVBoxLayout *vl = new QVBoxLayout(this);
	
	nameEdit = new QLineEdit(this);
	vl->addWidget(nameEdit);

	tutorEdit = new QLineEdit(this);
	vl->addWidget(tutorEdit);
}

NameWidget::~NameWidget()
{

}

void NameWidget::setSchueler(schueler *s)
{
    nameEdit->setText(s->getVorname().c_str());
    tutorEdit->setText(s->getTutor().c_str());
}

MarkWidget::MarkWidget(schueler *s, note *n, QWidget *parent, SeatEditor *editor)
	: QWidget(parent)//QPushButton(parent)
{
	seatEditor = editor;
	this->s = s;

	QHBoxLayout *la = new QHBoxLayout(this);
	bedit = new QPushButton("E",this);
	la->addWidget(bedit,10);
	bfehl = new QPushButton("X",this);
	la->addWidget(bfehl);
	
	if(n){
		this->n = n;
        // todo: bedit->setPixmap(GuiConfig::getInstance()->getIcon("note"));
		
	} else {
		this->n=0;
		qDebug("keine Note");
	}
	setMinimumHeight(50);
	setMinimumWidth(50);
	connect(bedit,SIGNAL(clicked()),this,SLOT(editNote()));
	connect(bfehl,SIGNAL(clicked()),this,SLOT(setFehlzeit()));
	//n=0;
}

MarkWidget::MarkWidget(schueler *s, stundenplaneintrag *e, QWidget *parent, SeatEditor *editor)
	: QWidget(parent) //QPushButton(parent)
{
	seatEditor = editor;
	this->s = s;
	this->e = e;
	this->bew = 0;
	
	QHBoxLayout *la = new QHBoxLayout(this);
	bedit = new QPushButton("",this);
	la->addWidget(bedit,10);

	//bfehl = new QPushButton("X",this);
	//la->addWidget(bfehl);
	
	if(s){
		if(fehlzeit *fz = e->getFehlzeit(s)){
			bedit->setText("--");
			//bedit->setEnabled(false);
			//bfehl->setEnabled(false);
		} else if ( (bew = e->getBewertung(s))  && (!bew->getGefehlt())){
            bedit->setText(bew->getBewertung().c_str());
			//bfehl->setEnabled(false);
		}
	}
	//setMinimumHeight(50);
	//setMinimumWidth(50);
	//connect(this,SIGNAL(clicked()),this,SLOT(editNote()));
	//n=0;
	connect(bedit,SIGNAL(clicked()),this,SLOT(editNote()));
	//connect(bfehl,SIGNAL(clicked()),this,SLOT(setFehlzeit()));
}

MarkWidget::~MarkWidget(){}

void MarkWidget::setMark(QString m)
{
	
}

void MarkWidget::editNote()
{
	//schueler *s = seatEditor->getSchueler();
	if(s){
		if(!bew){
			bew = (stundenbewertung*) GuiObjectFactory::getInstance()->create("stundenbewertung");
			//setPixmap(GuiConfig::getInstance()->getIcon("note"));
			bew->setSchueler(s);
			s->addToStundenbewertungen(bew);
			//bew->setStundenplaneintrag(e);
			if(e){
				e->addToBewertungen(bew);
				Transaction *t=Transactions::getCurrentTransaction();
				t->add(e);
				//t->add(bew);
			} else {
				qDebug("MarkWidget: WARNING: No stundenplaneintrag defined");
			}
		}
		seatEditor->editRequestor-> requestDialog(bew);
		if(bew){
			if(bew->getGefehlt()){
				setFehlzeit();
			} else {
                bedit->setText(bew->getBewertung().c_str());
			}	
			update();
			
		}
	} else {
		qDebug("MarkWidget: no schueler set: could not edit note");
	}
}

void MarkWidget::setFehlzeit()
{
	if(s){
		e->addFehlzeit(s);
		/*
		fehlzeit *fz = fehlzeitmapper::getInstance()->create();
		fz->setSchueler(s);
		fz->setVon(e->getDatum());
		s->addToFehlzeiten(fz);
		e->addToFehlzeiten(fz);
		*/

		
		bedit->setText("--");
		//bedit->setEnabled(false);
		//bfehl->setEnabled(false);
		
	}
}
