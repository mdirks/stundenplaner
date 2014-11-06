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
#ifndef KALENDERVIEW_H
#define KALENDERVIEW_H

#include <qwidget.h>
#include "gui/data/genericmap.h"
#include "gui/data/weekmap.h"
#include "gui/mapviews/weekmapview.h"
#include "gui/mapviews/daymapview.h"
#include "services/skalender.h"

#include "qpushbutton.h"

#include <kdatewidget.h>
/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class KalenderView : public QWidget
{

Q_OBJECT

public:
    KalenderView(QWidget *parent=0, const char* name=0);
    ~KalenderView();


    void setMap(WeekMap *map);

public slots:
	void setWeek();
	void incrementWeek();
	void decrementWeek();
public:
	WeekMapView *mapView;

private:
    GenericMap *map;
    
    KDateWidget *dateWidget;
    QPushButton *btor, *btol, *bset;
    int wnr;
    SKalender *skal;

};

class DayMapDisplay : public QWidget
{

Q_OBJECT

public:
    DayMapDisplay(QWidget *parent=0, const char* name=0);
    ~DayMapDisplay();


    void setMap(DayMap *map);

public slots:
	void setDay();
	void incrementDay();
	void decrementDay();
public:
	DayMapView *mapView;

private:
    GenericMap *map;
    
    KDateWidget *dateWidget;
    QPushButton *btor, *btol, *bset;
    int wnr;
    SKalender *skal;

};

#endif
