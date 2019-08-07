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
#ifndef DAYMAP_H
#define DAYMAP_H

#include "genericmap.h"

/**
@author Marcus Dirks
*/
class DayMap : public GenericMap
{
public:
    DayMap();
    ~DayMap();
    QDate getDate();
    void setDate(QDate date);

    void readStundenplan();

private:
	void clearStundenplan();
    
private:
    QGraphicsRectItem *morning, *afternoon, *evening;
	QDate date;
	list<QGraphicsItem*> *list_speintr;
};

#endif
