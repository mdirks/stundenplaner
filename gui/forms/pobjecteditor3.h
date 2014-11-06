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
#include <QTabWidget>

#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"
#include "gui/base/editrequestor.h"

/**	The standard form for PObjects, with dynamically generated fields.

	For a given object, editing fields are put together in the constructor based on information obtained via the repository.

	@author Marcus Dirks <marcus.dirks@web.de>
*/
class PObjectEditor3 : public /*QScrollArea*/ QWidget
{

Q_OBJECT

public:
    PObjectEditor3(PObject *o, QWidget *parent=0, list<RepositoryProperty*> *properties=0);
    ~PObjectEditor3();

public:
	EditRequestor *editRequestor;
    void addProperty(RepositoryProperty *rp);
    void addEditor(QWidget *w, QString title);

private:
	PObject *mo;
	RepositoryEntry *entry;
    QTabWidget *mainTab, *colTab;
	
};

#endif
