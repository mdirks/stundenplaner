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
#include "form_opo.h"
#include <list>

#include <qlayout.h>


form_opo::form_opo(QWidget *parent, const char *name)
 : QWidget(parent, name)
{
	labelTitle = new QLabel("Title",this);
	editTitle = new QLineEdit(this);
	buttonSave = new QPushButton("Save",this,"save");
	lbWidget= new PObjectListBoxWidget(this);

	QVBoxLayout *vbox = new QVBoxLayout(this);
	QHBoxLayout *hbox = new QHBoxLayout();
	vbox->addLayout(hbox,0);
	hbox->addWidget(labelTitle,0);
	hbox->addWidget(editTitle,10);
	
	vbox->addWidget(lbWidget,10);
	
	QHBoxLayout *hbox2 = new QHBoxLayout();
	vbox->addLayout(hbox2,0);
	hbox2->addStretch(10);
	hbox2->addWidget(buttonSave,0);
	
}


form_opo::~form_opo(){}

void form_opo::setObject(opo *o){
	this->o = o;
	
	editTitle->setText(o->getTitle());
	
	lbWidget->listBox->addObjects((std::list<PObject*>*) o->getMaterialien());
}


#include "form_opo.moc"
