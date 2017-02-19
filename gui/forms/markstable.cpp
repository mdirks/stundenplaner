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
#include "markstable.h"

#include "datamodel/klasse.h"
#include "datamodel/teilleistung.h"

#include <QDebug>

MarksTable::MarksTable(QWidget *parent, const char *name)
    : QTableWidget(parent)
{
	
}


MarksTable::~MarksTable()
{
}

void MarksTable::loadKlasse(klasse *kl)
{
    /*
    list<teilleistung*> *list_tl = kl->getTeilleistungen();
	setNumCols( list_tl->size() );


	int row =0;
	list<schueler*> *list_schueler = kl->getSchueler();
	for(list<schueler*>::iterator it = list_schueler->begin(); it != list_schueler ->end(); it++)
	{
		int col = 1;
		for(list<teilleistung*>::iterator itt=list_tl->begin(); itt!=list_tl->end(); it++)
		{
			note *n = (*itt)->getNote(*it);
			int pkt = n->getPunkte();
			setText(row,col,QString("%1").arg(pkt));
			col++;
		}
		row++;
	}
    */
    qDebug() << "Warning: MarksTable::loadKlasse() not implemented";
}

MarksDialog::MarksDialog(QWidget *parent) : QDialog(parent)
{
	marksTable = new MarksTable(this);
    //ToDo: does chooser show up, add to layout ?
    //setMainWidget(marksTable);

	resize(500,600);
	//this->mapper = mapper;
	
}

void MarksDialog::loadKlasse(klasse *kl)
{
	marksTable->loadKlasse(kl);
}


void MarksDialog::show(klasse *kl)
{
	MarksDialog *instance = new MarksDialog();
	instance->loadKlasse(kl);

	instance->exec();
}
