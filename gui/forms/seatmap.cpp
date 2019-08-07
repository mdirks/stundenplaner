//
// C++ Implementation: seatmap
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "seatmap.h"

#include "seateditor.h"
#include "datamodel/stundenplaneintrag.h"
#include "gui/base/guiconfig.h"
#include "gui/forms/pobjectdialog.h"
#include "services/sstundenplan.h"

#include <QLayout>
#include <QScrollArea>
//#include <qvbox.h>
#include <qdatetime.h>
#include <QDebug>



SeatMap::SeatMap(sitzplan *sp, QWidget *parent)
	:QWidget(parent)
{
	this->sp=sp;

	editRequestor = new EditRequestor();
	QVBoxLayout *l = new QVBoxLayout(this);

	QWidget *buttonWidget= new QWidget(this);
	QHBoxLayout *bwla = new QHBoxLayout(buttonWidget);
	QPushButton *bschueler = new QPushButton("Zeige Schueler",buttonWidget);
	connect(bschueler, SIGNAL(clicked()), this, SLOT(zeigeSchueler()));
	bwla->addWidget(bschueler);
	l->addWidget(buttonWidget);

    QScrollArea* sv = new QScrollArea(this);
	l->addWidget(sv,10);
        	
	QWidget *mainTab = new QWidget(sv->viewport());
    sv->setWidget(mainTab);
    //sv->setResizePolicy(QScrollView::AutoOneFit);
	
	
	QDate startDate = GuiConfig::getInstance()->getCurrentTermStart();
	QDate endDate = QDate::currentDate();
	//QDate endDate = GuiConfig::getInstance()->getCurrentTermEnd();
	
	QDate date = startDate;

	map<int, list<stundenplaneintrag*>* > map_eintraege;
	klasse *kl = sp->getKlasse();
	if(kl){
		int nweek=0;
		while(date < endDate){
            qDebug() << QString("Looking for eintraege on %1").arg(date.toString());

			//result->append(SStundenplan::getInstance()->getEintraegeForWeek(kl,date));
			map_eintraege[nweek]= SStundenplan::getInstance()->getEintraegeForWeek(kl,date);
			date=date.addDays(7);
			nweek++;
		}
	} else {
        qDebug() << "SeatMap::SeatMap : WARNING : sitzplan without klass";
	}
	

	int cols = sp->getSpalten();
	int rows = sp->getReihen();
    QGridLayout *layout = new QGridLayout(mainTab);
    if(cols == 0 || rows == 0) qDebug() << "SeatMap::SeatMap : WARNING  sitzplan ohne Inhalt";
	for(int i=1; i<=cols+1; i++){
		for(int j=1; j<=rows; j++){
			platz* pl= sp->getPlatz(j,i);
			SeatEditor *seatEditor = new SeatEditor(pl, sp->getKlasse(),map_eintraege, mainTab);
			layout->addWidget(seatEditor,j,i);
		}
	}
}

SeatMap::SeatMap(int cols, int rows, QWidget *parent)
	: QWidget(parent)
{	
	editRequestor = new EditRequestor();
	QVBoxLayout *l = new QVBoxLayout(this);
    QScrollArea* sv = new QScrollArea(this);
	l->addWidget(sv);
        	
	QWidget *mainTab = new QWidget(sv->viewport());
    sv->setWidget(mainTab);
    // todo : sv->setResizePolicy(QScrollView::AutoOneFit);
	map<int,list<stundenplaneintrag*> * > map_eintraege;
    QGridLayout *layout = new QGridLayout(mainTab);
	for(int i=1; i<=cols; i++){
		for(int j=1; j<=rows; j++){
			SeatEditor *seatEditor = new SeatEditor(0,0,map_eintraege,mainTab);
			connect(seatEditor->editRequestor,SIGNAL(dialogRequested(PObject*)),this->editRequestor,SLOT(requestDialog(PObject*)));
			layout->addWidget(seatEditor,i,j);
		}
	}
	
}


SeatMap::~SeatMap()
{
}




/*!
    \fn SeatMap::zeigeSchueler()
 */
void SeatMap::zeigeSchueler()
{
    if(sp && sp->getKlasse()){
	PObjectDialog::choosePObject((list<PObject*>*)sp->getKlasse()->getSchueler());
   } else {
	qDebug("SeatMap::zeigeSchueler(): invalid sitzplan or klasse, could not get schueler");
   }
}
