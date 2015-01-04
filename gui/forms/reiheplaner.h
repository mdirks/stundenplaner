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
#ifndef REIHEPLANER_H
#define REIHEPLANER_H

#include "datamodel/reihe.h"
#include "orm/repository/repositoryproperty.h"
#include "pobjectcombobox.h"
#include "gui/data/reihemap.h"
#include "pobjecticonview.h"
#include "pobjectlistprovider.h"

#include <QWidget>
#include <QTableWidget>
#include <QListWidget>
#include <QPixmap>

#include <list>

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class ReihePlaner : public QWidget {

Q_OBJECT

public:
    ReihePlaner(reihe *r=0, QWidget *parent=0);
    ~ReihePlaner();
    int numRows();
    void setNumRows(int num);
    void setReihe(reihe *r);


public slots:
    void currentChanged(int row, int col, int prow, int pcol);
    void activate(QListWidgetItem *item);

private:
	reihe *m_r;
    QListWidget *listW;
	RepositoryProperty *rp_verlauf, *rp_name, *rp_opos, *rp_material;
	int num_rows;
	QPixmap pm;


};


class ReihePlanerItem : public QWidget {

public:
    ReihePlanerItem(stunde *st, QListWidget *parent=0);

};


class ReiheBrowser : public QWidget {

Q_OBJECT

public:
    ReiheBrowser(RepositoryProperty *rp, PObject *po, QWidget *p=0);
    void setParentObject(PObject *po);

public slots:
    void indexChanged(int i);
    void nameChanged(QString s);

private:
    RepositoryProperty *m_rp;
    PObject *m_po;
    PObjectComboBox *box;
    //ReihePlaner *planer;
    PObjectIconView *planer;
    //ReiheMap *reiheMap;
    RpListProvider *provider;

};

#endif
