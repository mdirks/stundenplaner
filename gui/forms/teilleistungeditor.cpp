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
#include "teilleistungeditor.h"
#include "gui/actions/guicreateaction.h"
#include "gui/base/guiconfig.h"
#include "orm/transactions/transactions.h"
#include "datamodel/teilleistungberechnet.h"
#include "services/utils/namedobjectptrcomp.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/repository/repository.h"
#include "gui/guirepository.h"

#include <kinputdialog.h>
#include <QDebug>
#include <QToolBar>
#include <QVBoxLayout>

TeilleistungEditor::TeilleistungEditor(QWidget *parent, const char *name)
    : QTableWidget(parent)
{
	listSchueler = 0;
	listLeistungen = new list<teilleistung*>();

}


TeilleistungEditor::~TeilleistungEditor()
{
}

void TeilleistungEditor::editKlasse(klasse *kl)
{
	this->kl = kl;

	listSchueler = kl->getSchueler();
    setRowCount(listSchueler->size());
    setColumnCount(2);
	addSchuelerCol();
	columnLabels.append("Name");
	columnLabels.append("Vorname");
    setHorizontalHeaderLabels(columnLabels);
	


	//list<teilleistung*> *list_tl = kl->getTeilleistungen();
	
	RepositoryProperty *rp=Repository::getInstance()->getRepositoryEntry("klasse")->getProperty("Teilleistungen");
	list<teilleistung*> *list_tl = (list<teilleistung*>*) rp->asCollection(kl);
	for(list<teilleistung*>::iterator it = list_tl->begin(); it != list_tl->end(); it++){
		if(teilleistungberechnet *tlb = dynamic_cast<teilleistungberechnet*>(*it)){
			tlb->berechne();
		}
		addTeilleistung(*it);
	}
	setColumnSizes();
    resizeRowsToContents();
    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(setNote(int,int)));

}

void TeilleistungEditor::addTeilleistung(teilleistung *tl)
{
	if(! kl){
		kl = tl->getKlasse();
		if(!kl){
            qDebug() << "TeilleistungEditor::addTeilleistung : Klasse invalid in Teilleistung";
			return;
		}
	} else if(kl != tl->getKlasse()){
        qDebug() << "TeilleistungEdiotr::addTeilleistung(): Teilleistung has wrong klasse";
		//return;
	}

	
	
	listLeistungen->push_back(tl);
    columnLabels.append(tl->getName().c_str());

    setColumnCount(listLeistungen->size()+2);
	readNoten(tl,listLeistungen->size()+1);
    setHorizontalHeaderLabels(columnLabels);
	setColumnSizes();
    update();
}

void TeilleistungEditor::setColumnSizes()
{
    resizeColumnToContents(0);
    resizeColumnToContents(1);
    for(int i=2; i<listLeistungen->size()+2; i++){
		setColumnWidth(i,60);
	}
}

void TeilleistungEditor::addNewTeilleistung()
{
    QStringList classList=QString("klausur,teilleistung,teilleistungberechnet").split(",");

	teilleistung* tl = (teilleistung*) GuiCreateAction::getInstance()->createObject(classList);
	Transactions::getCurrentTransaction()->add(kl);
	kl->addToTeilleistungen(tl);

	QString name = KInputDialog::getText("Teilleistung","Bezeichnung");
    tl->setName(name.toStdString());
	

	for(list<schueler*>::iterator it=listSchueler->begin(); it != listSchueler->end(); it++){
		note *n = (note*) GuiCreateAction::getInstance()->create("note");
		n->setSchueler(*it);
		n->setName(tl->getName());
// 		Transactions::getCurrentTransaction()->add(*it);
// 		(*it)->addToNoten(n);
		tl->addToNoten(n);
	} 
	

	addTeilleistung(tl);
}

void TeilleistungEditor::addTeilleistungBerechnet()
{
	teilleistungberechnet* tl = (teilleistungberechnet*) GuiCreateAction::getInstance()->create("teilleistungberechnet");
	Transactions::getCurrentTransaction()->add(kl);
	kl->addToTeilleistungen(tl);
	

	for(list<schueler*>::iterator it=listSchueler->begin(); it != listSchueler->end(); it++){
		note *n = (note*) GuiCreateAction::getInstance()->create("note");
		n->setSchueler(*it);
		n->setName(tl->getName());
// 		Transactions::getCurrentTransaction()->add(*it);
// 		(*it)->addToNoten(n);
		tl->addToNoten(n);
	} 
	

	addTeilleistung(tl);
}

void TeilleistungEditor::addSchuelerCol()
{
	if(listSchueler){
		listSchueler->sort(NamedObjectPtrComp<PObject>());
		int r=0;
		QPixmap pm = GuiConfig::getInstance()->getIcon("schueler");
        pm=pm.scaled(10,10);
		for(list<schueler*>::iterator it = listSchueler->begin(); it != listSchueler->end(); it++){
            setItem(r,0,new QTableWidgetItem(pm,(*it)->getNachname().c_str()));
            setItem(r,1,new QTableWidgetItem((*it)->getVorname().c_str()));
			r++;
		}
	} else {

	}
	
}

void TeilleistungEditor::readNoten(teilleistung *tl, int c)
{
	int r=0;
	for(list<schueler*>::iterator it = listSchueler->begin(); it != listSchueler->end(); it++){
		note *n = tl->getNote(*it);
		if(n){
            setItem(r,c, new TlTableItem(n,this));
		} else { // for data-consistency create note if not available
			n = (note*) GuiCreateAction::getInstance()->create("note");
			if(n){
				n->setSchueler(*it);
				Transactions::getCurrentTransaction()->add(tl);
				tl->addToNoten(n);
                setItem(r,c,  new TlTableItem(n,this,true));
			} else {
                item(r,c)->setText("--");
			}
		}
		r++;
	}
}


void TeilleistungEditor::setNote(int r, int c)
{
	TlTableItem *i = (TlTableItem*) item(r,c);
	if(i){
		i->readNote();
	} else {
		qDebug("TeilleistungEditor::setNote : Warning : invalid TableItem");
	}
}


TlTableItem::TlTableItem(note *n, QTableWidget *table, bool w)
    : QTableWidgetItem()
{
	this->n = n;
	this->warn=w;
	setText(QString("%1").arg(n->getPunkte()));
}

void TlTableItem::readNote()
{
	if(n){
		qDebug("TlTableItem::readNote()");
		QString pkt = text();
		int pk = pkt.toInt();
		Transactions::getCurrentTransaction()->add(n);
		n->setPunkte(pk);
	} else {
		qDebug("TlTableItem::readNote : Warning : note invalid");
	}
}

/* todo
void TlTableItem::paint( QPainter *p, const QColorGroup &cg, const QRect &cr, bool selected )
{
    QColorGroup g( cg );
    // last row is the sum row - we want to make it more visible by
    // using a red background
    if ( warn )
        g.setColor( QColorGroup::Base, red );
    QTableItem::paint( p, g, cr, selected );
}
*/




TeilleistungEditorDialog::TeilleistungEditorDialog(klasse *kl, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *l =new QVBoxLayout(this);
    l->setSpacing(0);

    editor = new TeilleistungEditor(this);
	editor->editKlasse(kl);

    QToolBar *tb = new QToolBar(this);
    tb->addAction("Neu",editor,SLOT(addNewTeilleistung()));


    l->addWidget(tb);
    l->addWidget(editor);

    setToolTip(QString("Teilleistungen %1").arg(kl->getName().c_str()));

    //connect(this,SIGNAL(apply()),editor,SLOT(addNewTeilleistung()));
	//connect(this,SIGNAL(okClicked()),editor,SLOT(addTeilleistungBerechnet()));
}

void TeilleistungEditorDialog::slotOk()
{
	editor->addTeilleistungBerechnet();
}

void TeilleistungEditorDialog::edit(klasse *kl)
{
	TeilleistungEditorDialog *instance = new TeilleistungEditorDialog(kl);
    GuiRepository::getInstance()->showForm(instance);
}
