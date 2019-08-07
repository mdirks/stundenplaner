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
#include "stundenbewertungeneditor.h"
#include "datamodel/stundenbewertungmapper.h"
#include "gui/base/guiconfig.h"
#include "gui/actions/guicreateaction.h"
#include "orm/transactions/transactions.h"

#include <QTableWidget>
//#include "qlabel.h"
#include "qlayout.h"
#include "qpainter.h"
#include <QDialog>
#include <QLabel>

StundenbewertungenEditor::StundenbewertungenEditor(stundenplaneintrag *se, QWidget *parent, const char *name)
    :QTableWidget(parent)
{
	this->se = se;
	listSchueler=0;
	if(se){
		if(klasse *kl = se->getKlasse()){
			listSchueler = kl->getSchueler();
		}
	}
	
    setColumnCount(4);
	if(listSchueler){
        setRowCount(listSchueler->size()-1);
	}

	addSchuelerCol();
	readBewertungen();
	columnLabels.append("Name");
	columnLabels.append("Vorname");
	columnLabels.append("Bewertung");
	columnLabels.append("Bemerkung");
    setHorizontalHeaderLabels(columnLabels);
	setColumnWidth(3,400);
    //setColumnStretchable(3,true);
    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(setBewertung(int,int)));
    connect(this,SIGNAL(cellActivated(int,int)),this,SLOT(beginEdit(int,int)));

}



StundenbewertungenEditor::~StundenbewertungenEditor()
{
}
void StundenbewertungenEditor::beginEdit(int row, int col)
{
    beginEdit(row,col,false);
}

QWidget* StundenbewertungenEditor::beginEdit(int row, int col, bool replace)
{
	if(SbDummyTableItem *dti = dynamic_cast<SbDummyTableItem*>(item(row,col))){
		schueler *s = dti->getSchueler();
		stundenbewertung *bew = (stundenbewertung*) GuiCreateAction::getInstance()->create("stundenbewertung");
		Transaction *t=Transactions::getCurrentTransaction();
		bew->setStundenplaneintrag(se);
		bew->setSchueler(s);
		s->addToStundenbewertungen(bew);
		se->addToBewertungen(bew);
		t->add(s);
		t->add(se);

        setItem(row,2, new SbTableItemPunkte(bew,this));
        setItem(row,3, new SbTableItemBemerkung(bew,this));
		return 0; //return new QTableItem(this);
	} else {
        //todo : return QTableWidget::beginEdit(row,col,replace);
	}
}


void StundenbewertungenEditor::addSchuelerCol()
{
	if(listSchueler){
		int r=0;
		QPixmap pm = GuiConfig::getInstance()->getIcon("schueler");
		for(list<schueler*>::iterator it = listSchueler->begin(); it != listSchueler->end(); it++){
			//setPixmap(r,0,pm);
            QString nn = QString::fromStdString((*it)->getNachname());
            QString vn = QString::fromStdString((*it)->getVorname());
            setItem(r,0, new QTableWidgetItem(pm,nn));
            setItem(r,1, new QTableWidgetItem(pm,nn));
            /*
            item(r,0)->setText((*it)->getNachname().c_str());
            item(r,1)->setText((*it)->getVorname().c_str());
            */
			r++;
		}
	} else {

	}
	
}

void StundenbewertungenEditor::readBewertungen()
{
	int r=0;
	for(list<schueler*>::iterator it = listSchueler->begin(); it != listSchueler->end(); it++){
		stundenbewertung *bew = se->getBewertung(*it);
		if(bew){
            setItem(r,2, new SbTableItemPunkte(bew,this));
            setItem(r,3, new SbTableItemBemerkung(bew,this));
		} else {
            setItem(r,2, new SbDummyTableItem((*it),this));
            setItem(r,3, new SbDummyTableItem((*it),this));
		}
		r++;
	}
}


void StundenbewertungenEditor::setBewertung(int r, int c)
{
	SbTableItem *i = dynamic_cast<SbTableItem*>( item(r,c) );
    if(i){
		i->readBewertung();
	} else {
		qDebug("TeilleistungEditor::setNote : Warning : invalid TableItem");
	}
}


/*
void SbDummyTableItem::paint ( QPainter *p, const QColorGroup & cg, const QRect & cr, bool selected )
{
	QColorGroup g( cg );
	g.setColor( QColorGroup::Base, QColor(220,220,220) );
        QTableItem::paint( p, g, cr, selected );

	//QTableItem::paint(pai,cg,cr,selected);
}
*/

SbTableItem::SbTableItem(stundenbewertung *bew, QTableWidget *table)
    : QTableWidgetItem()
{
	this->bew=bew;
}

SbTableItemPunkte::SbTableItemPunkte(stundenbewertung *bew, QTableWidget *table)
    : SbTableItem(bew,table)
{
	//this->bew = bew;
    setText(QString("%1").arg(bew->getBewertung().c_str()));
}

void SbTableItemPunkte::readBewertung()
{
	if(bew){
		qDebug("SbTableItem::readPunkte()");
		//QString pkt = text();
		//int pk = pkt.toInt();
		Transactions::getCurrentTransaction()->add(bew);
        bew->setBewertung(text().toStdString());
	} else {
		qDebug("TlTableItem::readNote : Warning : note invalid");
	}
}

SbTableItemBemerkung::SbTableItemBemerkung(stundenbewertung *bew, QTableWidget *table)
    : SbTableItem(bew,table)
{
    setText(QString("%1").arg(bew->getBemerkung().c_str()));
}

void SbTableItemBemerkung::readBewertung()
{
	if(bew){
		qDebug("SbTableItem::readBemerkung()");
		//QString bem = text();
		//int pk = pkt.toInt();
		Transactions::getCurrentTransaction()->add(bew);
        bew->setBemerkung(text().toStdString());
	} else {
		qDebug("TlTableItem::readNote : Warning : note invalid");
	}
}



StundenbewertungenEditorDialog::StundenbewertungenEditorDialog(stundenplaneintrag *se, QWidget *parent)
    : QDialog(parent)
{
    //ToDo: does chooser show up, add to layout ?
    //setButtons(Apply|Close);
	QWidget *mainWidget = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(mainWidget);

    QString label = QString("%1 -- %2").arg(se->getName().c_str()).arg((se->getDatum()).toString());
	layout->addWidget(new QLabel(label,mainWidget));
	layout->addWidget(new StundenbewertungenEditor(se,mainWidget));

    //setMainWidget(mainWidget);

	//connect(this,SIGNAL(apply()),editor,SLOT(addNewTeilleistung()));
}

void StundenbewertungenEditorDialog::edit(stundenplaneintrag *se)
{
	StundenbewertungenEditorDialog *instance = new StundenbewertungenEditorDialog(se);
	instance->exec();
	
}
