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
#ifndef FILTEREDITOR_H
#define FILTEREDITOR_H

#include "services/filter/propertyfilter.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"

#include <QListWidgetItem>
#include <QDialog>

/**
	@author Marcus Dirks <m-dirks@web.de>
*/


class FilterEditorItem : public QListWidgetItem{
public: 
    FilterEditorItem(RepositoryProperty *rp, QListWidgetItem *parent);
	void activate();
	PropertyFilter* getFilter();
private:
	PropertyFilter *filter;
	RepositoryProperty *rp;
};

class FilterEditor : public QListWidget {
public:
    FilterEditor(RepositoryEntry *re, QWidget *parent=0);
    ~FilterEditor();
	AbstractFilter *getFilter();
	void addFilterFromChild(FilterEditorItem *fei);
	
private:
	RepositoryEntry *re;
	AbstractFilter *rootFilter;
	bool hasContents;
    QListWidgetItem *root;
};

class FilterEditorDialog : public QDialog {
public:
	FilterEditorDialog(RepositoryEntry *re, QWidget *parent=0);
	AbstractFilter *getFilter();
    static AbstractFilter* createFilter(RepositoryEntry *re);

private:
	FilterEditor *filterEditor;
};

#endif
