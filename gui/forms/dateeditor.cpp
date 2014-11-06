//
// C++ Implementation: dateeditor
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "dateeditor.h"
#include "orm/transactions/transactions.h"
#include "gui/guirepository.h"
#include "gui/base/guicontroler.h"

DateEditor::DateEditor(QWidget *parent)
 : KDateWidget(parent) /*QDateEdit(parent)*/
{
}

DateEditor::DateEditor(PObject *o, RepositoryProperty *prop, QWidget *parent) : KDateWidget(parent) /*QDateEdit(parent)*/
{
	this->prop = prop;
	this->parent = o;

	setDate(prop->asDate(o));

	connect(this,SIGNAL(changed( QDate)),this,SLOT(startEdit()));
}


DateEditor::~DateEditor()
{
	prop = 0;
	parent = 0;

	
}




/*!
    \fn DateEditor::startEdit(RepositoryProperty *rp, PObject *parent)
 */
void DateEditor::startEdit(RepositoryProperty *rp, PObject *parent)
{
    this->prop = rp;
    this->parent = parent;

    setDate(prop->asDate(parent));
	
    startEdit();
}


/*!
    \fn DateEditor::startEdit()
 */
void DateEditor::startEdit()
{
    if(prop && parent){
	Transactions::getCurrentTransaction()->add(parent);
	GuiControler::getInstance()->addActiveEditor(  this );
    }
}


/*!
    \fn DateEditor::stopEdit()
 */
void DateEditor::stopEdit()
{
	if(prop && parent){
		QDate d = date();
        prop->fromString(d.toString().toStdString(), parent);
	}

}
