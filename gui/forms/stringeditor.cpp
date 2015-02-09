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

StringEditor::StringEditor(QWidget *parent) : QLineEdit(parent), AbstractPropertyEditor()
{
    connect(this,SIGNAL(textChanged(QString &)),this,SLOT(startEdit(const QString &text)));
};
 
StringEditor::StringEditor(PObject *o, RepositoryProperty *prop, QWidget *p) :
    QLineEdit(p), AbstractPropertyEditor(o,prop)
{
    //this->property = prop;
    //this->parentObject = o;
	
    setText(AbstractPropertyEditor::property->asString( parentObject ).c_str());

    connect(this,SIGNAL(textChanged(const QString &)),this,SLOT(startEdit(const QString &text)));
    //connect(this,SIGNAL(returnPressed()),this,SLOT(stopEdit()));
}



void StringEditor::startEdit(RepositoryProperty *prop, PObject *o)
{
    this->AbstractPropertyEditor::property = prop;
    this->parentObject = o;
	
    setText(AbstractPropertyEditor::property->asString( parentObject ).c_str());
	AbstractPropertyEditor::startEdit();
}
 
void StringEditor::stopEdit()
{
    AbstractPropertyEditor::property->fromString(text().toStdString(), parentObject);
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

