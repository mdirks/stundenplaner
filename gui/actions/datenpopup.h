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
#ifndef DATENPOPUP_H
#define DATENPOPUP_H

#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/repository/repositoryentry.h"
#include "datamodel/klasse.h"
#include "datamodel/stundenplaneintrag.h"

#include <QMenu>
#include <QAction>

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class DatenPopup : public QMenu
{
Q_OBJECT

public:
    DatenPopup(PObject *o, QWidget *parent);
    ~DatenPopup();

};


class ShowCollectionAction : public QAction 
{

Q_OBJECT

public:
	ShowCollectionAction(PObject *o, RepositoryProperty *rp, QObject *parent);
	~ShowCollectionAction();

public slots:
	void showCollection();

private:
	PObject *o;
	RepositoryProperty *rp;
};

class ShowObjectAction : public QAction 
{
Q_OBJECT

public:
	ShowObjectAction(PObject *o, RepositoryProperty *rp, QObject *parent);
	~ShowObjectAction();

public slots:
	void showObject();

private:
	PObject *o;
	RepositoryProperty *rp;
};


class ShowPropertyAction : public QAction 
{
Q_OBJECT

public:
	ShowPropertyAction(PObject *o, RepositoryProperty *rp, QObject *parent);
	~ShowPropertyAction();

public slots:
	void showProperty();

private:
	PObject *o;
	RepositoryProperty *rp;
};


class ShowTeilleistungenAction : public QAction
{
Q_OBJECT

public:
	ShowTeilleistungenAction(klasse *kl);
	~ShowTeilleistungenAction(){};

public slots:
	void showTeilleistungen();

private:
	klasse *kl;
};

class EditBewertungenAction : public QAction
{
Q_OBJECT

public:
	EditBewertungenAction(stundenplaneintrag *se);
	
public slots:
	void editBewertungen();
private:
	stundenplaneintrag *se;
};


#endif
