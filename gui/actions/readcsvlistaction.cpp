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
#include "readcsvlistaction.h"
#include "datamodel/klasse.h"
#include "guicreateaction.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/transactions/transactions.h"

#include <qfile.h>
#include <qtextstream.h>
#include <kfiledialog.h>
#include <QDebug>

#define NAME "ReadCsv"

ReadCsvlistAction::ReadCsvlistAction()
{
	
}


ReadCsvlistAction::~ReadCsvlistAction()
{
}

void ReadCsvlistAction::reg()
{
	RepositoryProperty *rp = Repository::getInstance()->getRepositoryEntry("klasse")->getProperty("Schueler");
	rp->registerAction(NAME,this);
}

void ReadCsvlistAction::perform()
{
	if(o){
		perform(o);
	} else {
		qDebug("ReadCsvlist::perform() called but no object set");
	}
}

void ReadCsvlistAction::perform(PObject *o)
{
	QString filename = KFileDialog::getOpenFileName();
	perform(o,filename);

}


void ReadCsvlistAction::perform(PObject *o, QString filename)
{
	if(o){
		klasse *kl = dynamic_cast<klasse*>(o);
		if(kl){
			QFile file(filename);
            file.open(QIODevice::ReadOnly);
			QTextStream ts( &file );
			//ts.setEncoding(QTextStream::UnicodeUTF8);
			Transaction *t = Transactions::getCurrentTransaction();
			t->add(kl);
			while(! ts.atEnd() ){
				QString s = ts.readLine();
                qDebug() << s;
				
				
				QString nachname = s.section(",",0,0);
				QString vorname = s.section(",",1,1);
				QString tutor = s.section(",",2,2);

				schueler *sch = (schueler*) GuiCreateAction::getInstance()->create("schueler");
				if(sch){
                    sch->setName(s.toStdString());
                    sch->setNachname(nachname.toStdString());
                    sch->setVorname(vorname.toStdString());
                    sch->setTutor(tutor.toStdString());
					sch->setKlasse(kl);
					kl -> addToSchueler(sch);

				
					t->add(sch);
				} else {
                    qWarning() << "Failed to create schueler";
				}
				
			
			}
		} else {
            qWarning() << "ReadCsvlistAction: given object not of type klasse";
		}
	} else {
        qWarning() << "ReadCsvlistAction: given object was null";
	}
}

/*!
    \fn ReadCsvlistAction::newInstance()
 */
PropertyAction* ReadCsvlistAction::newInstance()
{
    return new ReadCsvlistAction();
}
