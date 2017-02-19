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
#ifndef PROPERTYCHOOSER_H
#define PROPERTYCHOOSER_H

#include "orm/mapping/abstractmapper.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/repository/repositoryentry.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeWidget>
#include <QDialog>


/**
	@author Marcus Dirks <m-dirks@web.de>
*/


class PropertyChooserItem : public QTreeWidgetItem {
public:
    PropertyChooserItem(RepositoryEntry *re, RepositoryProperty *rp, QTreeWidgetItem *parent);
    PropertyChooserItem(RepositoryEntry *re, RepositoryProperty *rp, QTreeWidget *parent);
	RepositoryProperty* getProperty();
	void activate();
private:
	RepositoryProperty *rp;
	RepositoryEntry *re_root;
	bool activated;
	
};

class PropertyChooser : public QTreeWidget {
public:
    PropertyChooser(AbstractMapper *mapper, QWidget *parent);
    ~PropertyChooser();

    RepositoryProperty* selectedProperty();


private:
	AbstractMapper *mapper;
};

class PropertyListChooser : public QWidget {

Q_OBJECT

public:
	PropertyListChooser(AbstractMapper *mapper, QWidget *parent);
	
	list<RepositoryProperty*>* selectedProperties();
	void addProperty(RepositoryEntry *re, RepositoryProperty* rp);

public slots:
	void addSelected();
	void removeSelected();

private:
	PropertyChooser *viewChooser;
    QTreeWidget *viewSelected;
    QTreeWidgetItem *rootViewSelected;
	RepositoryEntry *re_root;


};

class PropertyChooserDialog : public QDialog{
public:
	PropertyChooserDialog(AbstractMapper *mapper, QWidget *parent=0L);
	
	RepositoryProperty* selectedProperty();
	static RepositoryProperty* chooseProperty(AbstractMapper *mapper);

private:
	PropertyChooser *chooser;
};

class PropertylistChooserDialog : public QDialog{
public:
	PropertylistChooserDialog(AbstractMapper *mapper, QWidget *parent=0L);
	
	list<RepositoryProperty*>* selectedProperties();
	static list<RepositoryProperty*>* chooseProperties(AbstractMapper *mapper);

private:
	PropertyListChooser *chooser;
};

#endif
