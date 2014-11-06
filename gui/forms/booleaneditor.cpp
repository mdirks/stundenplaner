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
#include "booleaneditor.h"

BooleanEditor::BooleanEditor(PObject *o, RepositoryProperty *prop, QWidget *p)
	: QCheckBox(p)
{
	this->prop = prop;
	this->parent = o;
	
	setChecked(prop->asBoolean(o));

	connect(this,SIGNAL(stateChanged(int)),this,SLOT(startEdit(int)));
}


BooleanEditor::~BooleanEditor()
{
}

void BooleanEditor::startEdit(RepositoryProperty *prop, PObject *o)
{
	this->prop = prop;
	this->parent = o;
	
	setChecked(prop->asBoolean( parent ));
	AbstractPropertyEditor::startEdit();
}

void BooleanEditor::startEdit(int s)
{
	AbstractPropertyEditor::startEdit();
}

void BooleanEditor::stopEdit()
{
    if(isChecked()){
		prop->fromString("true", parent);
	} else {
		prop->fromString("false", parent);
	}
	
	AbstractPropertyEditor::stopEdit();
}
