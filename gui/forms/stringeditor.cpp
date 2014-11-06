//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "stringeditor.h"

#include "gui/base/guicontroler.h"

StringEditor::StringEditor(QWidget *parent) : QLineEdit(parent) 
{
	connect(this,SIGNAL(textChanged(QString &)),this,SLOT(startEdit()));
};
 
StringEditor::StringEditor(PObject *o, RepositoryProperty *prop, QWidget *p) : parent(o), property(prop), QLineEdit(p)
{
	this->property = prop;
	this->parent = o;
	
    setText(property->asString( parent ).c_str());

	connect(this,SIGNAL(textChanged(const QString &)),this,SLOT(startEdit()));
}



void StringEditor::startEdit(RepositoryProperty *prop, PObject *o)
{
	this->property = prop;
	this->parent = o;
	
    setText(property->asString( parent ).c_str());
	AbstractPropertyEditor::startEdit();
}
 
void StringEditor::stopEdit()
{
    property->fromString(text().toStdString(), parent);
	AbstractPropertyEditor::stopEdit();
	//editing = false;
	//parent->save();
	//clear();
}

void StringEditor::startEdit(const QString &text)
{
	startEdit();
}

/*!
    \fn StringEditor::startEdit()
 */

void StringEditor::startEdit()
{
    AbstractPropertyEditor::startEdit();
    
    /*	
    if(!editing){
	GuiControler::getInstance()->addActiveEditor(this);
	editing=true;
   }
   */
   


}

