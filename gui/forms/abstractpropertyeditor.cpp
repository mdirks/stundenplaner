//
// C++ Implementation: abstractpropertyeditor
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "abstractpropertyeditor.h"
#include "gui/guirepository.h"
#include "gui/base/guicontroler.h"

AbstractPropertyEditor::AbstractPropertyEditor()
 : parent(0), property(0)
{
	editRequestor = new EditRequestor();
}

AbstractPropertyEditor::AbstractPropertyEditor(PObject *o, RepositoryProperty *p)
 : parent(o), property(p)
{
	editRequestor = new EditRequestor();
}
AbstractPropertyEditor::~AbstractPropertyEditor()
{
}




/*!
    \fn AbstractPropertyEditor::startEdit()
 */
void AbstractPropertyEditor::startEdit()
{
     if(!editing){
	GuiControler::getInstance()->addActiveEditor(this);
	editing=true;
   }
}


/*!
    \fn AbstractPropertyEditor::stopEdit()
 */
void AbstractPropertyEditor::stopEdit()
{
    	if(parent) parent->save();
	editing=false;
}
