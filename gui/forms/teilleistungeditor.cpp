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
#include "gui/dialogs/collectionselectiondialog.h"

#include <kinputdialog.h>
#include <QDebug>
#include <QToolBar>
#include <QVBoxLayout>
#include <QPrinter>
#include <QPrintDialog>



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
    disconnect(this,SLOT(setNote(int,int)));
    this->clear();
    columnLabels.clear();
    delete listLeistungen;
    listLeistungen = new list<teilleistung*>();


    this->kl = kl;

	listSchueler = kl->getSchueler();
    setRowCount(listSchueler->size());
    setColumnCount(2);
	addSchuelerCol();
	columnLabels.append("Name");
	columnLabels.append("Vorname");
    setHorizontalHeaderLabels(columnLabels);
	


	//list<teilleistung*> *list_tl = kl->getTeilleistungen();
	
    QStringList displayList = GuiConfig::getInstance()->getDisplayProperties(
                QString("TeilleistungEditor::%1").arg(kl->getName().c_str()));
    bool configured=false;
    if(!displayList.isEmpty()) configured=true;

	RepositoryProperty *rp=Repository::getInstance()->getRepositoryEntry("klasse")->getProperty("Teilleistungen");
	list<teilleistung*> *list_tl = (list<teilleistung*>*) rp->asCollection(kl);
    if(!configured){
        for(list<teilleistung*>::iterator it = list_tl->begin(); it != list_tl->end(); it++){
            displayList.append((*it)->getName().c_str());
            addTeilleistung(*it);
        }
    } else {
         for(int i=0;i<displayList.size(); i++){
             for(list<teilleistung*>::iterator it = list_tl->begin(); it != list_tl->end(); it++){
                 if(displayList.at(i) == (*it)->getName().c_str()){
                     addTeilleistung(*it);
                     break;
                 }
             }

         }
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

    if(teilleistungberechnet *tlb = dynamic_cast<teilleistungberechnet*>(tl)){
        tlb->berechne();
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

void TeilleistungEditor::reloadPunkte()
{
    if(kl) editKlasse(kl);
}


void TeilleistungEditor::configure()
{
    //list<teilleistung> *displayList = new list<teilleistung>();
    RepositoryProperty *rp = Repository::getInstance()->getRepositoryEntry("klasse")->
            getProperty("Teilleistungen");
    CollectionSelectionDialog *ce = new CollectionSelectionDialog(kl,rp,this);

    //ConfigEditor *ce = new ConfigEditor(listLeistungen,kl,this);
    GuiRepository::getInstance()->showDialog(ce);

    listLeistungen=(list<teilleistung*>*)ce->getSelection();
    QStringList nameList;
    for(list<teilleistung*>::iterator it=listLeistungen->begin(); it!=listLeistungen->end(); it++){
        nameList.append((*it)->getName().c_str());
    }

    GuiConfig::getInstance()->setDisplayProperties(QString("TeilleistungEditor::%1").arg(kl->getName().c_str()),
                                                   nameList);

}

void TeilleistungEditor::editTeilleistung()
{
    int sel=currentColumn()-2;
    if(listLeistungen && sel >=0 && listLeistungen->size() > sel){
        list<teilleistung*>::iterator it=listLeistungen->begin();
        std::advance(it,sel);
        teilleistung *tl = *it;
        if(teilleistungberechnet *tlb=dynamic_cast<teilleistungberechnet*>(tl)){
            if(!tlb->getKlasse() && kl) tlb->setKlasse(kl);
            TlbEditor *ed = new TlbEditor(tlb,this);
            GuiRepository::getInstance()->showDialog(ed);
        } else {
            qDebug() << QString("Dont know how  to edit %1").arg(tl->getName().c_str());
        }
    }

}

void TeilleistungEditor::print()
{
    QPrinter printer;
    QPrintDialog printer_dialog(&printer);
    if (printer_dialog.exec() == QDialog::Accepted) {
        QPainter painter;
        painter.begin(&printer);
        double xscale = printer.pageRect().width()/double(this->width());
        double yscale = printer.pageRect().height()/double(this->height());
        double scale = qMin(xscale, yscale);
        painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                           printer.paperRect().y() + printer.pageRect().height()/2);
        painter.scale(scale, scale);
        painter.translate(-width()/2, -height()/2);

        this->render(&painter);
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
            setItem(r,c, new TlTableItem(n,tl, this));
		} else { // for data-consistency create note if not available
			n = (note*) GuiCreateAction::getInstance()->create("note");
			if(n){
				n->setSchueler(*it);
				Transactions::getCurrentTransaction()->add(tl);
				tl->addToNoten(n);
                setItem(r,c,  new TlTableItem(n, tl, this,true));
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


TlTableItem::TlTableItem(note *n, teilleistung *tl, QTableWidget *table, bool w)
    : QTableWidgetItem()
{
	this->n = n;
    this->tl = tl;
	this->warn=w;
    if(dynamic_cast<teilleistungberechnet*>(tl)){
        setBackground(QBrush(Qt::lightGray));
    }
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

ConfigEditor::ConfigEditor(list<teilleistung*> *displayList, klasse *kl, QWidget *parent)
{
    RepositoryProperty *rp = Repository::getInstance()->getRepositoryEntry("klasse")->
            getProperty("Teilleistungen");
    listAll = new PObjectIconView(rp,kl);

    listDisplay = new PObjectIconView(this);
    PoLListProvider *prov = new PoLListProvider((list<PObject*>*)displayList,"teilleistung");
    listDisplay->setObjectListProvider(prov);

    QLabel *labelDisplay = new QLabel("Display");
    QLabel *labelAll = new QLabel("Alle");

    QWidget *wDisplay = new QWidget(this);
    QVBoxLayout *lDisplay = new QVBoxLayout(wDisplay);
    lDisplay->addWidget(labelDisplay);
    lDisplay->addWidget(listDisplay);

    QWidget *wAll = new QWidget(this);
    QVBoxLayout *lAll = new QVBoxLayout(wAll);
    lAll->addWidget(labelAll);
    lAll->addWidget(listAll);

    QHBoxLayout *l = new QHBoxLayout(this);
    l->setSpacing(0);
    l->addWidget(wDisplay);
    l->addWidget(wAll);
}

TlbEditor::TlbEditor(teilleistungberechnet *tlb, QWidget *parent)
{

    RepositoryProperty *rp = Repository::getInstance()->getRepositoryEntry("teilleistungberechnet")->
            getProperty("Teilleistungen");
    listIs = new PObjectIconView(rp,tlb);

    listOptions = new PObjectIconView(this);
    if(tlb){
        if(klasse *kl = tlb->getKlasse()){
            list<teilleistung*> *ltl = kl->getTeilleistungen();
            PoLListProvider *prov = new PoLListProvider((list<PObject*>*)ltl,"teilleistung");
            listOptions->setObjectListProvider(prov);
        }
    }

    QLabel *labelIs = new QLabel(tlb->getName().c_str());
    QLabel *labelOptions = new QLabel("Alle");

    QWidget *wIs = new QWidget(this);
    QVBoxLayout *lIs = new QVBoxLayout(wIs);
    lIs->addWidget(labelIs);
    lIs->addWidget(listIs);

    QWidget *wOptions = new QWidget(this);
    QVBoxLayout *lOptions = new QVBoxLayout(wOptions);
    lOptions->addWidget(labelOptions);
    lOptions->addWidget(listOptions);

    QHBoxLayout *l = new QHBoxLayout(this);
    l->setSpacing(0);
    l->addWidget(wIs);
    l->addWidget(wOptions);
}



TeilleistungEditorDialog::TeilleistungEditorDialog(klasse *kl, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *l =new QVBoxLayout(this);
    l->setSpacing(0);

    editor = new TeilleistungEditor(this);
    if(kl){
        editor->editKlasse(kl);
    }

    QToolBar *tb = new QToolBar(this);
    tb->addAction("Neu",editor,SLOT(addNewTeilleistung()));
    tb->addAction("Reload",editor,SLOT(reloadPunkte()));
    tb->addAction("Edit",editor,SLOT(editTeilleistung()));
    tb->addAction("Config",editor,SLOT(configure()));
    tb->addAction("Print",editor,SLOT(print()));

    l->addWidget(tb);
    l->addWidget(editor);

    if(kl){
        setToolTip(QString("Teilleistungen %1").arg(kl->getName().c_str()));
    } else {
        setToolTip(QString("Teilleistungen"));
    }

    //connect(this,SIGNAL(apply()),editor,SLOT(addNewTeilleistung()));
	//connect(this,SIGNAL(okClicked()),editor,SLOT(addTeilleistungBerechnet()));
}

void TeilleistungEditorDialog::setKlasse(klasse *kl)
{
    editor->editKlasse(kl);
    setToolTip(QString("Teilleistungen %1").arg(kl->getName().c_str()));
}

void TeilleistungEditorDialog::setParentObject(PObject *o)
{
    if(klasse* kl=dynamic_cast<klasse*>(o)){
        editor->editKlasse(kl);
    } else {
        qDebug() << "WARNING: TeilleistungEditorDialog::setParentObject: can handle klasse only";
    }
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
