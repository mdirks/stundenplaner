//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef WEEKMAP_H
#define WEEKMAP_H


#include <QDateTime>
#include <list>


#include "genericmap.h"
#include "datamodel/stundenplan.h"
#include "datamodel/schultag.h"


using namespace std;


/**  This is the Gui-Element representing a whole week. 

	Main functionality is  inhereted from GenericMap. Date-time is handeled as Graphics positions.

	\todo Implement a week-object in the data - model 


@author Marcus Dirks
*/
class WeekMap : public GenericMap
{
public:
    enum Orientation {
        Horizontal=0,
        Vertical=1
    };

    WeekMap(WeekMap::Orientation=Vertical);
    ~WeekMap();
    QDate getStartDate();
    void setStartDate(QDate date);
    stundenplan* getStundenplan();
    void setStundenplan(stundenplan *sp);
    void displayMap();
void addItem(PObject *o, QDateTime datetime);
    void addItem(PObject *o, QPoint point);
void addItem(schultag *st);
void readStundenplan();
void clearStundenplan();

protected:
	QDate getDateForPosition(QPoint pos);
	QPoint getPositionForDate(QDateTime date);
    	QTime getTimeForStunde(int nrs);
	//QPoint getPositionForDate(QDate date, int stunde);
        void doElementLayout();

private:
    QGraphicsRectItem* partofdays[7*3];
    QGraphicsRectItem* dayheaders[7];
    qreal pod_width, pod_height, header_height;
	QDate start_date;
	stundenplan *sp;
	list<stundenplaneintrag*> *list_eintraege;
	list<QGraphicsItem*> *list_speintr;
    WeekMap::Orientation ori;

	
};

#endif
