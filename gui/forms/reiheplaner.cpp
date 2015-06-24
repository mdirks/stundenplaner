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
#include "reiheplaner.h"
#include "datamodel/stunde.h"
#include "gui/base/guiconfig.h"
#include "gui/forms/textpropertyeditor.h"
#include "gui/forms/stringeditor.h"
#include "gui/forms/pobjecticonview.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/transactions/transactions.h"
#include "gui/base/guiobjectfactory.h"
#include "gui/forms/stringeditor.h"
#include "orm/transactions/transactions.h"
#include "gui/mapviews/genericmapview.h"
//#include "actions/createaction.h"
//#include <qvbox.h>
#include <QLayout>
#include <QTableWidget>
#include <QLabel>
#include <list>

using namespace std;

ReiheBrowser::ReiheBrowser(RepositoryProperty *rp, PObject *po, QWidget *p)
    : QWidget(p),
      ui(new Ui::ReiheBrowser)
{
    //m_rp = rp;
    m_po = po;

    ui->setupUi(this);

    RepositoryProperty *rp_verlauf = Repository::getInstance()->getRepositoryEntry("stunde")->getProperty("Verlauf");
    ui->textViewer->setProperty(rp_verlauf);

    rp_stunden = Repository::getInstance()->getRepositoryEntry("reihe")->getProperty("Stunden");
    rp_notes = Repository::getInstance()->getRepositoryEntry("reihe")->getProperty("Notizen");
    rp_materialien = Repository::getInstance()->getRepositoryEntry("reihe")->getProperty("Materialien");


    connect(ui->selector,SIGNAL(currentRowChanged(int)),this,SLOT(selectorIndexChanged(int)));
    connect(ui->planer,SIGNAL(currentRowChanged(int)),this,SLOT(planerIndexChanged(int)));



}

void ReiheBrowser::selectorIndexChanged(int i)
{
        PObject *o = ui->selector->getCurrent();
        if(reihe *r = dynamic_cast<reihe*>(o)){
            ui->planer->setObjectListProvider(new RpListProvider(rp_stunden,r));
        } else {
            ui->planer->clear();
        }

}

void ReiheBrowser::planerIndexChanged(int i)
{
        PObject *o = ui->planer->getCurrent();
        if(stunde *s = dynamic_cast<stunde*>(o)){
            ui->textViewer->setParentObject(s);
            ui->listNotes->setObjectListProvider(new RpListProvider(rp_notes,s));
            ui->listMaterial->setObjectListProvider(new RpListProvider(rp_materialien,s));
        } else {
            ui->textViewer->setParentObject(0);
        }

}

void ReiheBrowser::nameChanged(QString newName)
{
    PObject *o=ui->selector->getCurrent();
    if(reihe* r=dynamic_cast<reihe*>(o))
    {
        Transactions::getCurrentTransaction()->add(r);
        r->setName(newName.toStdString());
    }
}

/* set klasse to be edited */
void ReiheBrowser::setParentObject(PObject *po)
{
    disconnect(ui->selector);
    ui->selector->disconnect(this);
    ui->planer->disconnect(this);

    ui->planer->clear();
    m_po = po;
    RepositoryProperty *rp_reihen= Repository::getInstance()->getRepositoryEntry("klasse")->getProperty("Reihen");
    ui->selector->setObjectListProvider(new RpListProvider(rp_reihen,m_po));
    ui->titleLabel->setText(QString("Reiheplaner: %1").arg(m_po->getName().c_str()));

    connect(ui->selector,SIGNAL(currentRowChanged(int)),this,SLOT(selectorIndexChanged(int)));
    connect(ui->planer,SIGNAL(currentRowChanged(int)),this,SLOT(planerIndexChanged(int)));
}


ReihePlanerItem::ReihePlanerItem(stunde *st, QListWidget *parent)
    : QWidget(parent)
{

    QHBoxLayout *hl = new QHBoxLayout();
    RepositoryProperty *rpName = Repository::getInstance()->getRepositoryEntry("stunde")->getProperty("Name");
    StringEditor *nameEditor = new StringEditor(st,rpName,this);
    QLabel *la = new QLabel();
    la->setPixmap(GuiConfig::getInstance()->getIcon(st).scaledToHeight(12));
    hl->addWidget(la);
    hl->addWidget(nameEditor);

    QVBoxLayout *l = new QVBoxLayout();

    l->addLayout(hl);
    RepositoryProperty *rp = Repository::getInstance()->getRepositoryEntry("stunde")->getProperty("Verlauf");
    l->addWidget(new TextPropertyViewer(st,rp,this));


    setLayout(l);
    //setText(st->getName().c_str());
}


ReihePlaner::ReihePlaner(reihe *r, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
	l->setMargin(20);
    listW = new QListWidget(this);
    connect(listW,SIGNAL(itemActivated(QListWidgetItem*)),this,SLOT(activate(QListWidgetItem*)));
    l->addWidget(listW);



	pm = GuiConfig::getInstance()->getIcon("stunde");

	
	RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry("stunde");
	rp_verlauf = re->getProperty("Verlauf");
	rp_name = re->getProperty("Name");
	rp_opos = re->getProperty("Opos");
	rp_material = re->getProperty("Materialien");
	

    connect(listW, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(currentChanged(int,int,int,int)));

    if(r){
        setReihe(r);
    }
}

void ReihePlaner::setReihe(reihe *r)
{
    m_r = r;
    listW->clear();

    list<stunde*> *list_stunden=r->getStunden();
    setNumRows(list_stunden->size()*2+1);

	int i=0;	
	for(list<stunde*>::iterator it = list_stunden->begin(); it!= list_stunden->end(); it++){
        // todo : m_table->setPixmap(i,0,pm);
		
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0,50));
        ReihePlanerItem *itemWidget = new ReihePlanerItem((*it),listW);
        listW->addItem(item);
        listW->setItemWidget(item, itemWidget);
        //itemWidget->show();

        /*
        StringEditor *str_editor = new StringEditor((*it), rp_name, m_table);
		m_table->setCellWidget(i,1,str_editor);
		m_table->setRowHeight(i,60);

		
		TextPropertyEditor *verl_editor = new TextPropertyEditor((*it), rp_verlauf, m_table);
		m_table->setCellWidget(i+1,1,verl_editor);
		m_table->setRowHeight(i+1,200);

		PObjectIconView *opo_view = new PObjectIconView(rp_opos, (*it), m_table);
		opo_view-> load();
		m_table->setCellWidget(i+1,2,opo_view);

		
		PObjectIconView *material_view = new PObjectIconView(rp_material, (*it), m_table);
		material_view-> load();
		m_table->setCellWidget(i+1,3,material_view);
		
        i+=2;
        */


	}
    listW->addItem(new QListWidgetItem("Neue Stunde",listW));


}


ReihePlaner::~ReihePlaner()
{
}

void ReihePlaner::currentChanged(int row, int col, int prow, int pcol)
{
	
	qDebug("PObjectTable::currentChanged");
    /*
	if(row == numRows()-1){
		qDebug("Adding element");

		PObject *o;
		Transactions::getCurrentTransaction()->add(m_r);
		//string className = prop->getType();
		stunde *st = dynamic_cast<stunde*>( GuiObjectFactory::getInstance()->create("stunde") );
		if(st){
		   m_r->addToStunden(st);
		}
	
		int i= numRows()-1;
		setNumRows(row+3);
        // todo : m_table->setPixmap(i,0,pm);
		
		StringEditor *str_editor = new StringEditor(st, rp_name, m_table);	
		m_table->setCellWidget(i,1,str_editor);
		m_table->setRowHeight(i,60);

		
		TextPropertyEditor *verl_editor = new TextPropertyEditor(st, rp_verlauf, m_table);
		m_table->setCellWidget(i+1,1,verl_editor);
		m_table->setRowHeight(i+1,200);

		PObjectIconView *opo_view = new PObjectIconView(rp_opos, st, m_table);
		opo_view-> load();
		m_table->setCellWidget(i+1,2,opo_view);

		PObjectIconView *material_view = new PObjectIconView(rp_material, st, m_table);
		material_view-> load();
		m_table->setCellWidget(i+1,3,material_view);
		m_table-> update();

		
	} else {
        qDebug() << QString("Current changed: %1, %2").arg(row).arg(col);
	}
    */
}

void ReihePlaner::activate(QListWidgetItem *item)
{
    if(item->text() == "Neue Stunde"){
        stunde *st = (stunde*) GuiObjectFactory::getInstance()->create("stunde");
        Transactions::getCurrentTransaction()->add(m_r);
        m_r->addToStunden(st);
        setReihe(m_r);
    }
}

int ReihePlaner::numRows(){
	return num_rows;
}

void ReihePlaner::setNumRows(int num)
{
    //m_table->setRowCount(num);
	num_rows=num;
}
