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
#include "testindirectrepositoryproperty.h"

#include "datamodel/datamodelrepository.h"
#include "datamodel/schueler.h"
#include "datamodel/note.h"
#include "datamodel/klasse.h"

#include "gui/actions/guicreateaction.h"

#include "orm/transactions/transactions.h"
#include "orm/persistence/database.h"

#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"

TestIndirectRepositoryProperty::TestIndirectRepositoryProperty()
{
}


TestIndirectRepositoryProperty::~TestIndirectRepositoryProperty()
{
}

void TestIndirectRepositoryProperty::run()
{
	DataModelRepository::getInstance();
	note *n = (note*) GuiCreateAction::getInstance()->create("note");
	schueler *s = (schueler*) GuiCreateAction::getInstance()->create("schueler");
	klasse *kl = (klasse*) GuiCreateAction::getInstance()->create("klasse");

	kl->setName("K1");
	s->setVorname("V1");
	s->setNachname("V2");
	s->setKlasse(kl);
	n->setSchueler(s);
	Transactions::getCurrentTransaction()->commit();
	//Database::getInstance()->close();

	RepositoryEntry *re=Repository::getInstance()->getRepositoryEntry("note");
	RepositoryProperty *rp = 0;

	rp = re->getProperty("Schueler/Vorname");
	if(!rp){fail("Could not get indirect property Schueler/Vorname");return;}

	if(rp->asString(n) != "V1"){fail("Could not recover value for schueler name");return;}

	rp = re->getProperty("Schueler/Nonsense");
	if(rp){fail("Could get nonsense property");return;}

	rp = re->getProperty("Schueler/Klasse/Name");
	if(!rp){fail("Could not get Schueler/Klasse/Name");return;}
	if(rp->asString(n) != "K1"){fail("Could not recover value for klasse name"); return;}
	


	publish("Erfolg");

}
