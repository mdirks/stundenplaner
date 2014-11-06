//
// C++ Implementation: fileeditor
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "fileeditor.h"



FileEditor::FileEditor(QWidget *parent)
 /*: KURLRequester(parent)*/ /*QDateEdit(parent)*/
{
}

FileEditor::FileEditor(PObject *o, RepositoryProperty *prop, QWidget *parent) /*: KURLRequester(parent)*/ /*QDateEdit(parent)*/
{
	this->prop = prop;
	this->parent = o;

	//setDate(prop->asDate(o));

	//connect(this,SIGNAL(changed( QDate)),this,SLOT(startEdit()));
}

/*
void FileEditor::startEdit(RepositoryProperty *rp, PObject *parent)
{
    
}
*/

void FileEditor::startEdit()
{
   
}


void FileEditor::stopEdit()
{
	
}


