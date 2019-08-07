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
#include "testreadcsvlistaction.h"
#include "datamodel/datamodelrepository.h"
#include "datamodel/klasse.h"
#include "gui/actions/guicreateaction.h"
#include "gui/actions/readcsvlistaction.h"


TestReadCsvlistAction::TestReadCsvlistAction()
{
}


TestReadCsvlistAction::~TestReadCsvlistAction()
{
}

void TestReadCsvlistAction::run()
{
	DataModelRepository::getInstance();
	klasse *kl = (klasse*) GuiCreateAction::getInstance()->create("klasse");
	
	 (new ReadCsvlistAction())->perform(kl,"/home/mopp/schueler-test.txt");

	if(kl->getSchueler()->size() != 3){fail("Schueler nicht korrekt angelegt"); return;}
	publish("Erfolg");
}
