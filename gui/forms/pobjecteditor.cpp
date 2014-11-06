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
#include "pobjecteditor.h"

#include "pobjectlistview.h"
#include "textpropertyeditor.h"
#include "repositoryitem.h"
#include "stringeditor.h"

#include <qlayout.h>

PObjectEditor::PObjectEditor(PObject *mo, QWidget *parent)
 : QWidget(parent)
{
    this->rootObject = mo;
    
    QHBoxLayout *hbox = new QHBoxLayout(this);
    QVBoxLayout *vbox = new QVBoxLayout();
    
    listView = new PObjectListView(this);
    hbox->addWidget(listView,1);
    listView->setObject(mo);
    //listView->setFixedSize(300,300);
    //listView->show();
    
    hbox->addLayout(vbox,3);
    
    
    stringEditor = new StringEditor(this);
    vbox->addWidget(stringEditor);
    
    textEditor = new TextPropertyEditor(this);
    vbox->addWidget(textEditor);
    //textEditor->show();
    
    activeEditor=0;
    
    connect(listView, SIGNAL(selectionChanged(QListViewItem* )), this, SLOT(selectionChanged(QListViewItem* )));
    
}


PObjectEditor::~PObjectEditor()
{
}

void PObjectEditor::selectionChanged(QListWidgetItem *item)
{
	if(activeEditor){
		activeEditor->stopEdit();
		activeEditor=0;
	}
	
	if(RepositoryItem *ritem = dynamic_cast<RepositoryItem*>(item))
	{
		RepositoryProperty *rp = ritem->getRepositoryProperty();
		PObject *parent = ritem->getParent();
		if(rp->isText()){
			activeEditor = textEditor;
			textEditor->startEdit(rp,parent);
		} else if (rp->isString()) {
			activeEditor = stringEditor;
			stringEditor->startEdit(rp,parent);
		}
	}
}
