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
#ifndef GENERICMAPVIEWCONTROLER_H
#define GENERICMAPVIEWCONTROLER_H

#include "gui/mapviews/genericmapview.h"

#include "qobject.h"
#include "qpoint.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class GenericMapViewControler : public QObject {

Q_OBJECT

public:
    GenericMapViewControler(GenericMapView *mapView);
    ~GenericMapViewControler();

protected:
    virtual QMenu* getPopupMenu();

public slots:
	void createNewItem();
	void deleteSelected();
	void itemDown();
    void itemUp();
    void fit();
	virtual void activateSelected(PObjectGraphicsItemNP *selectedItem);
	void showFormForSelected();
	void writeLatex();
	void showPopup(QPoint pos);
	
	
	

protected:
	QPoint pos;
private:
	GenericMapView *mapView;
	bool isPlanning;

};

#endif
