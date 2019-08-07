//
// C++ Interface: pobjecteditor2
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef POBJECTEDITOR2_H
#define POBJECTEDITOR2_H

#include <QWidget>
#include <QScrollArea>
//#include <qscrollview.h>

#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"
#include "gui/base/editrequestor.h"

/**	The standard form for PObjects, with dynamically generated fields.

	For a given object, editing fields are put together in the constructor based on information obtained via the repository.

	@author Marcus Dirks <marcus.dirks@web.de>
*/
class PObjectEditor2 : public QScrollArea /*QWidget*/
{

Q_OBJECT

public:
    PObjectEditor2(PObject *o, QWidget *parent=0, list<RepositoryProperty*> *properties=0);
    ~PObjectEditor2();

public:
	EditRequestor *editRequestor;

private:
	PObject *mo;
	RepositoryEntry *entry;
	
};

#endif
