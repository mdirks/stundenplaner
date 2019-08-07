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
#ifndef STUNDENBEWERTUNGENEDITOR_H
#define STUNDENBEWERTUNGENEDITOR_H

#include "datamodel/stundenplaneintrag.h"

#include <QTableWidget>
#include <QDialog>
#include <list>

using namespace std;

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class StundenbewertungenEditor : public QTableWidget {

Q_OBJECT

public:
    StundenbewertungenEditor(stundenplaneintrag *se, QWidget *parent=0, const char *name=0);
    ~StundenbewertungenEditor();

public slots:
	void setBewertung(int r, int c);
    void beginEdit(int r, int c);

protected:
	QWidget* beginEdit(int row, int col, bool replace);	
	void addSchuelerCol();
	void readBewertungen();

private:
	stundenplaneintrag *se;
	list<schueler*> *listSchueler;
	QStringList columnLabels;
};




class SbDummyTableItem : public QTableWidgetItem {

public:
    SbDummyTableItem(schueler *s, QTableWidget *table) : QTableWidgetItem(){this->s=s;};
	virtual ~SbDummyTableItem(){};

	schueler* getSchueler(){return s;}
    void paint ( QPainter * p,  const QRect & cr, bool selected );
protected:
	schueler *s;
};



class SbTableItem : public QTableWidgetItem {

public:
    SbTableItem(stundenbewertung *bew, QTableWidget *table);
	virtual ~SbTableItem(){};

	virtual void readBewertung()=0;

protected:
	stundenbewertung *bew;
};


class SbTableItemPunkte : public SbTableItem {

public:
    SbTableItemPunkte(stundenbewertung *bew, QTableWidget *table);
	virtual ~SbTableItemPunkte(){};

	virtual void readBewertung();

};


class SbTableItemBemerkung : public SbTableItem {


public:
    SbTableItemBemerkung(stundenbewertung *bew, QTableWidget *table);
	virtual ~SbTableItemBemerkung(){};

	virtual void readBewertung();


};


class StundenbewertungenEditorDialog : public QDialog
{
public:
	StundenbewertungenEditorDialog(stundenplaneintrag *se, QWidget *parent=0);
	~StundenbewertungenEditorDialog(){};

	static void edit(stundenplaneintrag *se);
	
};
#endif
