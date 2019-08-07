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
#include "testqdatetime.h"

#include "qdatetime.h"
#include "datamodel/stunde.h"
#include "datamodel/datamodelrepository.h"
#include "datamodel/fehlzeit.h"
#include "datamodel/fehlzeitmapper.h"
#include "datamodel/stundenplaneintrag.h"
#include "datamodel/stundenplaneintragmapper.h"
#include "orm/transactions/transactions.h"
#include "orm/persistence/database.h"
#include "services/actions/createaction.h"
#include <map>
#include "stdlib.h"
#include <QDebug>

using namespace std;

TestQDateTime::TestQDateTime()
{
}


TestQDateTime::~TestQDateTime()
{
}


void TestQDateTime::run()
{
	map<QDateTime,stunde*> mapTimeStunde;
    QLocale::setDefault(QLocale::German);
    //setenv("LC_ALL","de_DE.UTF-8",1);
    // test basic Date handling
    qDebug() << QDate::currentDate().toString();
    QDate date = QDate::fromString("Mo Dec 22 2014");
    if(!date.isValid()){fail("could not read QDate from string");return;}

    Variant v = QVariant("Di Mai 26 2015");
    date=v.asQDate();
    if(!date.isValid()){fail("could not get date from variant");return;}

	DataModelRepository::getInstance();
	stunde *st = (stunde*) CreateAction::getInstance()->create("stunde");

	int id_st = st->getID();	

	QDateTime dt(QDate::currentDate(), QTime(7,50).addSecs(2*60*45) );
	mapTimeStunde[dt] = st;

	/*
	Transactions::getCurrentTransaction()->commit();
	Database::getInstance()->close();

	PObject *o = Database::getInstance()->loadObjectById(id_st);
	st = dynamic_cast<stunde*>(o);
	*/

	QDateTime dt2(QDate::currentDate(), QTime(7,50).addSecs(2*60*45) );
	stunde *mst = mapTimeStunde[dt2];
	if(!mst){fail("Date-Key ergab keine Stunde");return;}
	if(mst != st){fail("Falsche Stunde in der Map"); return;}

	// test QDate persistence
	stundenplaneintrag *se = (stundenplaneintrag*) stundenplaneintragmapper::getInstance()->create();
	QDate cd = QDate::currentDate();
	se->setDatum(cd);
	int se_id = se->getID();
	
	Transactions::getCurrentTransaction()->commit();
	Database::getInstance()->close();
	qDebug("DB closed");
	
	PObject *o =Database::getInstance()->loadObjectById(se_id);
	if(!o){ fail("Could not even recover object form db");return;}
	stundenplaneintrag *see = dynamic_cast<stundenplaneintrag*>(o);
	if(!see){fail("Could not recover stundenplaneintrag form db");return;}
	if(see->getDatum() != cd){fail("date in stundenplaneintrag not saved");return;}


	// test QDateTime persistence
	fehlzeit *fz = (fehlzeit*) fehlzeitmapper::getInstance()->create();
	QDateTime current = QDateTime::currentDateTime();
	fz->setVon(current);
	int fz_id = fz->getID();
	
	Transactions::getCurrentTransaction()->commit();
	Database::getInstance()->close();
	
	
	o =Database::getInstance()->loadObjectById(fz_id);
	fehlzeit *fzz = dynamic_cast<fehlzeit*>(o);
	if(!fzz){fail("Could not recover fehlzeit form db");return;}
	if(fzz->getVon() != current){fail("von time not saved");return;}

	publish("Erfolg");
}
