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
#include "pobjectlistboxwidget.h"
#include <qlayout.h>

PObjectListBoxWidget::PObjectListBoxWidget(QWidget *parent, const char *name)
 :  QWidget(parent,name)
{
	listBox = new PObjectListBox(this);
	buttonNew = new QPushButton("New",this,"new");
	buttonDelete = new QPushButton("Delete",this,"delete");
	
	QHBoxLayout *hbox = new QHBoxLayout(this);
	QVBoxLayout *vbox = new QVBoxLayout();
	
	hbox->addWidget(listBox,10);
	hbox->addLayout(vbox,0);
	vbox->addWidget(buttonNew,0);
	vbox->addWidget(buttonDelete,0);
	vbox->addStretch(10);

}


PObjectListBoxWidget::~PObjectListBoxWidget()
{
}


#include "pobjectlistboxwidget.moc"
