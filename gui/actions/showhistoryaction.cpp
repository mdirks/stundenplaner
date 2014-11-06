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
#include "showhistoryaction.h"

#include "datamodel/stundenplantemplateeintrag.h"
#include "gui/guirepository.h"
#include "orm/repository/repository.h"
#include "services/sstundenplan.h"

#include <QDebug>

ShowHistoryAction::ShowHistoryAction(stundenplaneintrag *se, QObject *parent)
    : QAction("Historie", parent)
{
	this->se = se;
	connect(this, SIGNAL( activated() ) , this, SLOT( showHistoryForStundenplaneintrag() ) );
}


ShowHistoryAction::~ShowHistoryAction()
{
}


void ShowHistoryAction::showHistoryForStundenplaneintrag()
{
	if(se){
		stundenplaneintrag *prev = SStundenplan::getInstance()->getPrevious(se);
		if(prev){
			list<RepositoryProperty*> *properties = new list<RepositoryProperty*>();
			RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry("stundenplaneintrag");
			if(re){
				RepositoryProperty *rp = re->getProperty("Fehlzeiten");
				if(rp) properties->push_back(rp);
				rp = re->getProperty("Bewertungen");
				if(rp) properties->push_back(rp);
				rp = re->getProperty("Verlauf");
				if(rp) properties->push_back(rp);
				rp = re->getProperty("Datum");
				if(rp) properties->push_back(rp);
			}

			GuiRepository::getInstance()->showDialogForObject(prev,properties);
		} else {
                qDebug() << "ShowHistoryAction::showHistoryForStundenplaneintrag : Could not get previous Eintrag";
		}
	} else {
        qDebug() << "ShowHistoryAction::showHistoryForStundenplaneintrag : No Eintrag set";
	}
}
