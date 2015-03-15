// 
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "weekmap.h"
#include "weekmapmapper.h"
#include "icongraphicsitem.h"
#include "schultaggraphicsitem.h"
#include "schultaggraphicsitemmapper.h"
#include "datamodel/stundenplaneintrag.h"
#include "services/sstundenplan.h"

#include <qdatetime.h>

#define POD_HEIGHT  311.0
#define POD_WIDTH  170.0
#define HEADER_HEIGHT  60.0

WeekMap::WeekMap(WeekMap::Orientation o)
 : GenericMap(0,0) //GenericMap(5*POD_WIDTH,3*POD_HEIGHT+HEADER_HEIGHT)
{
    setMapper(WeekMapmapper::getInstance());

	pod_width=POD_WIDTH;
	pod_height=POD_HEIGHT;
	header_height=HEADER_HEIGHT;

    ori=o;


	sp=0;
    list_speintr = new list<QGraphicsItem*>();


    doElementLayout();

    update();

	
}

void WeekMap::doElementLayout()
{
    if(ori==Vertical){
        GenericMap::setSceneRect(0,0,3*pod_width,5*pod_height+2*header_height);
    } else {
        GenericMap::setSceneRect(0,0,6*pod_width,2.5*pod_height+header_height);
    }

    QString nameofdays[7] = {"Montag","Dienstag","Mittwoch","Donnerstag","Freitag","Wochenende"};

    for(int k=0; k<2; k++){
        for(int i = 0; i<3; i++){
            int col,row,ind;
            if(ori==Vertical){
                col=i;
                row=k;
            } else {
                col=3*k+i;
                row=0;
            }
            ind=3*k+i;
            int rowsep=row*(header_height+2.5*pod_height);

            /*
            IconGraphicsItem *ici = new IconGraphicsItem(col*pod_width,rowsep,pod_width,header_height,
                                                         nameofdays[ind],"config-date",this);
            ici->setBrush(QColor(175,203,230));
            ici->setPen(QColor(130,130,130));
            ici->show();
            ici->setZValue(-1.0);
            QGraphicsScene::addItem(ici);
            dayheaders[ind] = ici;
            */
            dayheaders[ind]=0;
            for(int j = 0; j<3; j++){
                partofdays[3*ind+j] = new QGraphicsRectItem(col*pod_width,rowsep+header_height+j*pod_height,
                                                          pod_width,pod_height);
                int greyscale = 230 - j*10;
                partofdays[3*ind+j] -> setBrush(QColor(greyscale,greyscale,greyscale));
                partofdays[3*ind+j] -> setPen(QColor(130,130,130));
                partofdays[3*ind+j]->show();
                //partofdays[3*i+j]->setZValue(-1.0);
                partofdays[3*ind+j]->setZValue(-1.0);
                QGraphicsScene::addItem(partofdays[3*ind+j]);
            }
        }
    }
}


WeekMap::~WeekMap()
{
}

QDate WeekMap::getDateForPosition(QPoint pos)
{


}

/*
QPoint WeekMap::getPositionForDate(QDateTime datetime)
{
	int x,y,h,d;
        
	d = datetime.date().dayOfWeek();
	if(d>6) d=6;
	x= (d-1)*pod_width+5;

	y = datetime.time().hour()*pod_height/6;

	return QPoint(x,y);
}
*/

QPoint WeekMap::getPositionForDate(QDateTime datetime)
{
	int x,y,h,d;

    int rowsep=0;

	d = datetime.date().dayOfWeek();
	if(d>6) d=6;
    if(d>3){
        rowsep=header_height+2.5*pod_height;
        d=d-3;
    }
    x= (d-1)*pod_width+5;

	h = datetime.time().hour();
	if(h>6){
		h=h-7;
        y = h*pod_height/6 + header_height+rowsep;
		
	} else if (h<7){
        y = 10+rowsep;
		qDebug("Weekmap: Found early hour !?");
	} 

	return QPoint(x,y);
}


QTime WeekMap::getTimeForStunde(int nrs)
{
	return QTime(7,50).addSecs(nrs*60*45); 
}
/*!
    \fn WeekMap::getStartDate()
 */
QDate WeekMap::getStartDate()
{
    return this->start_date;
}


/*!
    \fn WeekMap::setStartDate(QDate date)
 */
void WeekMap::setStartDate(QDate date)
{
    	this->start_date = date;
	

    for(int k=0; k<2; k++){
        for(int i = 0; i<3; i++){

            int col,row,ind;

            if(ori==Vertical){
                col=i;
                row=k;
            } else {
                col=3*k+i;
                row=0;
            }
            ind=3*k+i;

            int rowsep=row*(header_height+2.5*pod_height);

            if(dayheaders[ind]){
                removeItem(dayheaders[ind]);
                delete dayheaders[ind];
            }
            QString nameofday = date.addDays(ind+1).toString();
            IconGraphicsItem *ici = new IconGraphicsItem(col*pod_width,rowsep,pod_width,header_height,
                                                         nameofday,"config-date",this);
            ici->setBrush(QColor(175,203,230));
            ici->setPen(QColor(130,130,130));
            ici->show();
            ici->setZValue(-1.0);
            QGraphicsScene::addItem(ici);
            dayheaders[ind] = ici;
        }
    }

}

/*!
    \fn WeekMap::getStundenplan()
 */
stundenplan* WeekMap::getStundenplan()
{
    return this->sp;
}


/*!
    \fn WeekMap::setStundenplan(stundenplan *sp)
 */
void WeekMap::setStundenplan(stundenplan *sp)
{
//     if(this->sp != sp){
// 	this->sp = sp;
// 	//list<stundenplaneintrag*> *list_eintraege_alle = sp->getEintraege();
// 	 list_eintraege = new list<stundenplaneintrag*>();
// 	
// 	list<stundenplaneintrag*> *eintraege;
// 	QDate date1 = getStartDate();
// 	for(int i=0; i<5; i++){
// 		sp->getEintraege( list_eintraege, date1);	
// 		date1 = date1.addDays(1);
// 	}
// 	
//         for(list<stundenplaneintrag*>::iterator it = list_eintraege->begin(); it != list_eintraege->end(); it++){
// 		stundenplaneintrag* eintrag = (*it);
// 		addItem( eintrag, eintrag->getDatum() );
// 	}
// 	
//     }
   	qDebug("----- Warning ---------- \n WeekMap::setStundenplan() not implemented ! \n ------------- ");
}


/*!
    \fn WeekMap::displayMap()
 */
void WeekMap::displayMap()
{
      /*
      if(sp){
	QDate date = getStartDate();
	QDate date2 = date.addDays(5);
	list<stundenplaneintrag*>  *list_eintraege = sp->getEintraege();
	for(list<stundenplaneintrag*>::iterator it = list_eintraege->begin(); it != list_eintraege->end(); it++){
		stundenplaneintrag *eintrag = (*it);

	}
	*/
    
    GenericMap::displayMap();
}


/*!
    \fn WeekMap::addItem(PObject *o, QDateTime datetime)
 */
void WeekMap::addItem(PObject *o, QDateTime datetime)
{
    GenericMap::addItem( o, getPositionForDate( datetime ));
}


void WeekMap::addItem(PObject *o, QPoint point)
{
//     	if(schultag *st = dynamic_cast<schultag*>(o)){
// 		addItem(st);
// 	}
	GenericMap::addItem( o, point);
}


/*!
    \fn WeekMap::addItem(schultag *st)
 */
void WeekMap::addItem(schultag *st)
{
    if(! st){
	qDebug("Weekmap: Got invalid schultag - could not add");
	return;
    }
    /*
    PObjectGraphicsItem *item = (PObjectGraphicsItem*) PObjectGraphicsItemmapper::getInstance()->create();
    item->setObject(st);
    item->setWidth(120);
    item->etHeight(320);
    
    GenericMap::addGraphicsItem(item,getPositionForDate( st->getDatum() ));
    */
    list<stundenplaneintrag*> *list_eintraege = st->getEintraege();
    for(list<stundenplaneintrag*>::iterator it = list_eintraege->begin(); it != list_eintraege->end(); it++){
	stundenplaneintrag *e =(*it);
	PObjectGraphicsItemNP *sp_ei = GenericMap::addItemNP( e, getPositionForDate(QDateTime(e->getDatum(),getTimeForStunde(e->getNrStunde()))) );
	list_speintr->push_back(sp_ei);
    }
    //item->save();
}

void WeekMap::readStundenplan()
{
	clearStundenplan();
	QDate date = getStartDate();

	SStundenplan* ss = SStundenplan::getInstance();
	for(int i=0; i<6;i++){
		list<stundenplaneintrag*> *list_eintraege =  ss->getEintraege(  date.addDays(i) );
		for(list<stundenplaneintrag*>::iterator it = list_eintraege->begin(); it != list_eintraege->end(); it++){
			stundenplaneintrag *e =(*it);
			PObjectGraphicsItemNP *sp_ei = GenericMap::addItemNP( e, getPositionForDate(QDateTime(e->getDatum(),getTimeForStunde(e->getNrStunde()))) );
			list_speintr->push_back(sp_ei);
    		}
				
	}
	update();
}

void WeekMap::clearStundenplan()
{
	for(list<QGraphicsItem*>::iterator it = list_speintr->begin(); it!=list_speintr->end(); it++){
		(*it)->setVisible(false);
	}	
	list_speintr->clear();
}

