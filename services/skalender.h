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
#ifndef SKALENDER_H
#define SKALENDER_H


#include "gui/data/weekmap.h"
#include "gui/data/daymap.h"
#include "orm/transactions/transactionobject.h"

#include <map>

using namespace std;

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class SKalender : public TransactionObject {
public:
    SKalender();

    ~SKalender();
    static SKalender* getInstance();
    static void close();
    void setActiveSchuljahr(schuljahr *sj);

    WeekMap* getWeek(QDate date);
    list<WeekMap*>* getWeeks();
    void addToWeeks(WeekMap *wm);
    void deleteFromWeeks(WeekMap *);
    WeekMap* getCurrentWeek();

    DayMap* getDay(QDate date);
    list<DayMap*>* getDays();
    void addToDays(DayMap *dm);
    void deleteFromDays(DayMap *);
    DayMap* getCurrentDay();

    bool  isFerientag(QDate date);
    bool isSchultag(QDate date);
    QString getDescription(QDate date);
    bool isSchuljahr(QDate date);

    
private:
	void init();


private:
	static SKalender *instance;
	static schuljahr *active_sj;
	list<WeekMap*> *listWeeks;
	list<DayMap*> *listDays;
	map<QDate, WeekMap*> mapWeeks;
	map<QDate, DayMap*> mapDays;
    map<QDate, QString> mapFerien;
	static QDate von,bis;

};

#endif
