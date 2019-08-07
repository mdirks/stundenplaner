/***************************************************************************
 *   Copyright (C) 2008 by Marcus Dirks   *
 *   m-dirks@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "skalender.h"
#include "skalendermapper.h"
#include "orm/mapping/mappingcontroler.h"
#include "gui/data/weekmapmapper.h"
#include "orm/transactions/transactions.h"
#include "datamodel/ferien.h"
#include "gui/data/daymapmapper.h"
#include "services/sstundenplan.h"

#include "qpoint.h"
#include <QDebug>

SKalender* SKalender::instance=0;
schuljahr* SKalender::active_sj=0;
//map<QDate, QString>SKalender::mapFerien;
QDate SKalender::von;
QDate SKalender::bis;

void SKalender::setActiveSchuljahr(schuljahr *sj)
{
	active_sj =sj;
	getInstance()->init();
	mapFerien.clear();

	for(list<ferien*>::iterator it=sj->getFerien()->begin(); it!= sj->getFerien()->end(); it++){
		QDate d = (*it)->getVon();
		QDate bis = (*it)->getBis();
		while(d <= bis){
            mapFerien[d] = (*it)->getName().c_str();
			d=d.addDays(1);
		}
	}

	von = sj->getVon();
	bis = sj->getBis();
}



SKalender::SKalender()
{
	setMapper(SKalendermapper::getInstance());
	listWeeks = 0;
	listDays = 0;

	
	/*
	for(QDate date(2009,10,19); date <= QDate(2009,10,30); date=date.addDays(1)){
		mapFerien[date] = QString("Herbstferien 09/10");
	}
	for(QDate date(2009,12,21); date <= QDate(2010,1,2); date=date.addDays(1)){
		mapFerien[date] = QString("Weihnachtsferien 09/10");
	}
	for(QDate date(2010,2,1); date <= QDate(2010,2,6); date=date.addDays(1)){
		mapFerien[date] = QString("Winterferien 09/10");
	}
	for(QDate date(2010,3,31); date <= QDate(2010,4,10); date=date.addDays(1)){
		mapFerien[date] = QString("Osterferien 09/10");
	}
	for(QDate date(2010,5,25); date <= QDate(2010,5,25); date=date.addDays(1)){
		mapFerien[date] = QString("Pfingsten 09/10");
	}
	*/
	
}

void SKalender::init()
{
	
}


SKalender::~SKalender()
{
}




/*!
    \fn SKalender::getWeek(int weekNumber)
 */
WeekMap* SKalender::getWeek(QDate date)
{
    date = date.addDays(-date.dayOfWeek());
    WeekMap *wm = mapWeeks[date];
    if(!wm){
        list<WeekMap*> *lwm = SKalendermapper::getInstance()->findWeeks(getID(),
                                                                        "datum",date.toString().toStdString());
        if(lwm->size()>0){
            if(lwm->size()==1){
                wm=(*lwm->begin());
                mapWeeks[date]=wm;
            } else {
                qDebug() << "Strange: which weekmap to take ????";
            }
        } else {
            qDebug() << QString("Could not find WeekMap for %1 in SKalender, createing new one").arg(date.toString());
            wm = WeekMapmapper::getInstance()->create();
            if(wm){
                wm->setStartDate(date);
                addToWeeks(wm);
                Transactions::getCurrentTransaction()->add(this);
                mapWeeks[date]=wm;
            }else {
            qDebug() << "SKalender::getWeek: STRANGE: could not create week instance";
            }
        }

    }
    return wm;
    /*
    WeekMap *wm;
    getWeeks();
    date = date.addDays(-date.dayOfWeek());

    map<QDate,WeekMap*>::iterator it= mapWeeks.find(date);
    if(it != mapWeeks.end()){
        wm = it->second;
    } else {
        qDebug() << QString("Could not find WeekMap for %1 in SKalender, createing new one").arg(date.toString());
        wm = WeekMapmapper::getInstance()->create();
        if(wm){
            wm->setStartDate(date);
            addToWeeks(wm);
            Transactions::getCurrentTransaction()->add(this);
            mapWeeks[date]=wm;
        }else {
        qDebug() << "SKalender::getWeek: STRANGE: could not create week instance";
        }
    }

    return wm;
    */
}

/*!
    \fn SKalender::getDay(QDate date)
 */
DayMap* SKalender::getDay(QDate date)
{
	DayMap *dm=0;
	
	getDays();
	map<QDate,DayMap*>::iterator it = mapDays.find(date);
	if(it != mapDays.end()){
		dm = it->second;
	} else {
        qDebug() << QString("Skalender::getDay : No DayMap found for %1, creating new one").arg(date.toString());
		dm = DayMapmapper::getInstance()->create();
		if(dm){
			dm->setDate(date);
			addToDays(dm);
			Transactions::getCurrentTransaction()->add(this);
			mapDays[date] = dm;
            dm->setName(date.toString().toStdString());

			
		}else {
            qDebug() << "SKalender::getDay: STRANGE: could not create DayMap instance";
		}
	}
	return dm;
	
}


/*!
    \fn SKalender::getInstance()
 */
SKalender* SKalender::getInstance()
{
    if(!instance){
	MappingControler::getInstance()->registerPersistentClass(SKalendermapper::getInstance());
	list<PObject*> *result = SKalendermapper::getInstance()->find_gen();
	if(!result || result->size()==0){
		qDebug("No SKalender object defined creating new one");
		instance=SKalendermapper::getInstance()->create();
	} else {
		instance=dynamic_cast<SKalender*>((*(--(result->end()))));
	}
	
   }
   return instance;
}


/*!
    \fn SKalender::getWeeks()
 */
list<WeekMap*>* SKalender::getWeeks()
{
    if(!listWeeks){
        listWeeks = SKalendermapper::getInstance()->findWeeks(getID());
        for(list<WeekMap*>::iterator it = listWeeks->begin(); it!=listWeeks->end(); it++){
            QDate sdate =(*it)->getStartDate();
            mapWeeks[sdate] = (*it);
            qDebug() << QString("SKalender: Found weekmap for %1").arg(sdate.toString());
        }
    }
    return listWeeks;
}

/*!
    \fn SKalender::getWeeks()
 */
list<DayMap*>* SKalender::getDays()
{
    if(!listDays){
	listDays= SKalendermapper::getInstance()->findDays(getID());
	for(list<DayMap*>::iterator it = listDays->begin(); it!=listDays->end(); it++){
		QDate sdate =(*it)->getDate();
		mapDays[sdate] = (*it);
		//qDebug(QString("SKalender: Found weekmap for %1").arg(sdate.toString()));
	}
    }
    return listDays;
}

void SKalender::addToWeeks(WeekMap *wm)
{
    getWeeks()->push_back(wm);
}

void SKalender::deleteFromWeeks(WeekMap *wm)
{
     getWeeks()->remove(wm);
}

WeekMap* SKalender::getCurrentWeek()
{
    return getWeek(QDate::currentDate());
}

void SKalender::addToDays(DayMap *dm)
{
    getDays()->push_back(dm);
}

void SKalender::deleteFromDays(DayMap *dm)
{
    getDays()->remove(dm);
}

DayMap* SKalender::getCurrentDay()
{
    return getDay(QDate::currentDate());
}
/*!
    \fn SKalender::close()
 */
void SKalender::close()
{
    instance=0;
}


/*!
    \fn SKalender::isFerientag(QDate date)
 */
bool  SKalender::isFerientag(QDate date)
{
	if(! isSchuljahr(date)){
			return true;
	}
    map<QDate,QString>::iterator it = mapFerien.find(date);
	if(it != mapFerien.end()){
		return true;
	} 
	return false;
}


/*!
    \fn SKalender::isSchultag(QDate date)
 */
bool SKalender::isSchultag(QDate date)
{
    return (! isFerientag(date));
    //qDebug() << "WARNING: todo FIX SKalender::isSchultag()";
    //return true;
}


/*!
    \fn SKalender::getDescription(QDate date)
 */
QString SKalender::getDescription(QDate date)
{
	if(isFerientag(date)){
		map<QDate,QString>::iterator it = mapFerien.find(date);
		if(it != mapFerien.end()){
			return it->second;
		} else if( !isSchuljahr(date)){
			return "nicht im Schuljahr";
		} else {
			return "Strange";
		}
	} else {
		return "Schultag";
	}
}


/*!
    \fn SKalender::isSchuljahr(QDate date)
 */
bool SKalender::isSchuljahr(QDate date)
{
	if((date < von || date > bis)){
		return false;
	}
	return true;
}


