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
#ifndef MARKSTABLE_H
#define MARKSTABLE_H

#include "datamodel/klasse.h"

#include <QTableWidget>
#include <KDialog>
/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class MarksTable : public QTableWidget {
public:
    MarksTable(QWidget *parent=0, const char *name=0);
    ~MarksTable();
    void loadKlasse(klasse *kl);
};

class MarksDialog : public KDialog
{
public:
	MarksDialog(QWidget *parent=0L);
	
	static void show(klasse *kl);

private: 
	void loadKlasse(klasse *kl);

private:
	MarksTable *marksTable;
};
#endif
