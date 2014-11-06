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
#ifndef TEILLEISTUNGEDITOR_H
#define TEILLEISTUNGEDITOR_H

#include "datamodel/teilleistung.h"
#include "datamodel/klasse.h"
#include "datamodel/note.h"

#include <QTableWidget>
#include <QStringList>
#include <KDialog>
#include <list>

using namespace std;
/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class TeilleistungEditor : public QTableWidget {
Q_OBJECT

public:
    TeilleistungEditor(QWidget *parent=0, const char *name=0);
    ~TeilleistungEditor();

	void addTeilleistung(teilleistung *tl);
	void addSchuelerCol();
	void readNoten(teilleistung *tl, int c);
	void editKlasse(klasse *kl);

private:
	void setColumnSizes();

public slots:
	void setNote(int r, int c);
	void addNewTeilleistung();
	void addTeilleistungBerechnet();
	//void readNote(int r, int c);

private:
	bool hasSchuelerCol;
	klasse* kl;
	list<schueler*> *listSchueler;
	list<teilleistung*> *listLeistungen;
	QStringList columnLabels;

};



class TlTableItem : public QTableWidgetItem {



public:
    TlTableItem(note *n, QTableWidget *table, bool warn=false);
	virtual ~TlTableItem(){};

	virtual void readNote();
    //virtual void paint( QPainter *p,  const QRect &cr, bool selected );
private:
	note *n;
	bool warn;
};

class TeilleistungEditorDialog : public QWidget
{
Q_OBJECT
public:
	TeilleistungEditorDialog(klasse *kl, QWidget *parent=0);
	~TeilleistungEditorDialog(){};

	static void edit(klasse *kl);

protected slots:
	void slotOk();

private:
	TeilleistungEditor *editor;
	
};
#endif
