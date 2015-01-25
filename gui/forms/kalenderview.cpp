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
#include "kalenderview.h"

#include "qwidget.h"
#include "qlayout.h"
#include <QToolBar>

#include "gui/mapviews/genericmapview.h"
#include "orm/transactions/transactions.h"
#include "gui/actions/weekmapviewcontroler.h"

KalenderView::KalenderView(QWidget *parent, const char *name)
 : QWidget(parent)
{
	
	skal=SKalender::getInstance();
	QVBoxLayout *la = new QVBoxLayout(this);


    QToolBar *buttonWidget = new QToolBar(this);
    buttonWidget->setContentsMargins(0,0,0,0);
    //buttonWidget->setStyleSheet("background-color: yellow; border-width: 0pt");
    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);




    buttonWidget->addAction("<",this, SLOT(decrementWeek()));
    buttonWidget->addAction(">",this, SLOT(incrementWeek()));
    buttonWidget->addWidget(empty);
    dateWidget = new KDateWidget();


	mapView = new WeekMapView(this);
    mapView->setStyleSheet("border: 0px");
    la->setSpacing(0);
    la->setContentsMargins(0,0,0,0);

	la->addWidget(mapView,10);
    la->addWidget(buttonWidget);

    //setMinimumSize(800,410);
}


KalenderView::~KalenderView()
{
}


void KalenderView::setMap(WeekMap *map)
{
	mapView->setMap(map);
	Transactions::getCurrentTransaction()->add(map);
	QDate d = map->getStartDate();
    dateWidget->setDate(d);
	wnr = d.weekNumber();
	map->readStundenplan();
    mapView->fitInView(map->sceneRect(), Qt::KeepAspectRatio);
	
}

void KalenderView::setWeek()
{
    QDate isdate = dateWidget->date();
    wnr = isdate.weekNumber();
    setMap(skal-> getWeek(isdate));
}

void KalenderView::decrementWeek()
{
    QDate isdate = dateWidget->date();
	isdate = isdate.addDays(-6);
	setMap(skal->getWeek(isdate));
}

void KalenderView::incrementWeek()
{
	QDate isdate = dateWidget->date();
	isdate = isdate.addDays(8);
	setMap(skal->getWeek(isdate));
}

DayMapDisplay::DayMapDisplay(QWidget *parent, const char *name)
 : QWidget(parent)
{
	
	skal=SKalender::getInstance();
	QVBoxLayout *la = new QVBoxLayout(this);

    QWidget *buttonWidget = new QWidget(this);
	QHBoxLayout *bla = new QHBoxLayout(buttonWidget);
	btor = new QPushButton(">", buttonWidget);
	btol = new QPushButton("<", buttonWidget);
	bset = new QPushButton("Ok", buttonWidget);
	dateWidget = new KDateWidget(buttonWidget);

	connect(btor, SIGNAL(clicked()), this, SLOT(incrementDay()));
	connect(btol, SIGNAL(clicked()), this, SLOT(decrementDay()));
	connect(bset, SIGNAL(clicked()), this, SLOT(setDay()));

	
	
	bla->addWidget(btol);
	bla->addWidget(dateWidget);
	bla->addWidget(bset,10);
	bla->addWidget(btor);
	
	la->addWidget(buttonWidget);

	mapView = new DayMapView(this);
	//WeekMapViewControler *controler = new WeekMapViewControler(mapView);
	
	la->addWidget(mapView,10);
}


DayMapDisplay::~DayMapDisplay()
{
}


void DayMapDisplay::setMap(DayMap *map)
{
	mapView->setMap(map);
	Transactions::getCurrentTransaction()->add(map);
	QDate d = map->getDate();
	dateWidget->setDate(d);
	map->readStundenplan();
	
}

void DayMapDisplay::setDay()
{
	QDate isdate = dateWidget->date();
	//wnr = isdate.weekNumber();
	setMap(skal-> getDay(isdate));
}

void DayMapDisplay::decrementDay()
{
	QDate isdate = dateWidget->date();
	isdate = isdate.addDays(-1);
	setMap(skal->getDay(isdate));
}

void DayMapDisplay::incrementDay()
{
	QDate isdate = dateWidget->date();
	isdate = isdate.addDays(1);
	setMap(skal->getDay(isdate));
}

