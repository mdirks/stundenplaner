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
#include "daymap.h"
#include "daymapmapper.h"
#include "services/sstundenplan.h"

#include <qcolor.h>

DayMap::DayMap()
 : GenericMap(2000,1000)
{
	/*
	morning = new QGraphicsRectangle(0,0,500,300,this);
	afternoon = new QGraphicsRectangle(0,300,500,300,this);
	evening = new QGraphicsRectangle(0,600,500,300,this);
	
	morning->setBrush(QColor(250,250,250));
	afternoon->setBrush(QColor(240,240,240));
	evening->setBrush(QColor(230,230,230));
	
	morning->setZ(-1.0);
	afternoon->setZ(-1.0);
	evening->setZ(-1.0);
	
	morning->show();
	afternoon->show();
	evening->show();
	*/
	
	list_speintr = new list<QGraphicsItem*>();
	setMapper(DayMapmapper::getInstance());
}


DayMap::~DayMap()
{
}




/*!
    \fn DayMap::getDate()
 */
QDate DayMap::getDate()
{
    return this->date;
}


/*!
    \fn DayMap::setDate(QDate date)
 */
void DayMap::setDate(QDate date)
{
    this->date=date;
}

void DayMap::readStundenplan()
{
	clearStundenplan();

	
		list<stundenplaneintrag*> *list_e=SStundenplan::getInstance()->getEintraege(this->date);
        qDebug() << QString("Got %1 Eintraege for %2").arg(list_e->size()).arg(date.toString());
		QPoint pos = QPoint(10,10);
		QPoint increment = QPoint(0,150);
		for(list<stundenplaneintrag*>::iterator it = list_e->begin(); it!=list_e->end(); it++){
			stundenplaneintrag *e =(*it);
			PObjectGraphicsItemNP *sp_ei = addItemNP( e,pos); 
			list_speintr->push_back(sp_ei);
			pos=pos+increment;
		}

		QDate d=date.addDays(1);
		list_e=SStundenplan::getInstance()->getEintraege(d);
		pos = QPoint(1200,600);
		increment = QPoint(200,0);
		int count=1;
		for(list<stundenplaneintrag*>::iterator it = list_e->begin(); it!=list_e->end(); it++){
			stundenplaneintrag *e =(*it);
			PObjectGraphicsItemNP *sp_ei = addItemNP( e,pos); 
			list_speintr->push_back(sp_ei);
            qDebug() << "Added item for stundenplaneintrag";
            if(count==3){pos=pos+QPoint(-600,50);}
			pos=pos+increment;
			count++;
		}
        qDebug() << QString("DayMap::readStundenplan : added %1 items for %2!").arg(list_speintr->size()).arg(date.toString());

	
	update();
}

void DayMap::clearStundenplan()
{
	for(list<QGraphicsItem*>::iterator it = list_speintr->begin(); it!=list_speintr->end(); it++){
		(*it)->setVisible(false);
	}	
	list_speintr->clear();
}
