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
#ifndef SITZPLANMAPVIEWCONTROLER_H
#define SITZPLANMAPVIEWCONTROLER_H

#include "gui/mapviews/sitzplanmapview.h"
#include "genericmapviewcontroler.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class SitzplanMapViewControler : public GenericMapViewControler {

Q_OBJECT

public:
    SitzplanMapViewControler(SitzplanMapView *smapView);
    ~SitzplanMapViewControler();
    list<fehlzeit*>* getFehlzeitenForSchueler();
    
public slots:
	virtual void activateSelected(PObjectGraphicsItemNP *selectedItem);
	void addStundenbewertung();
	void addFehlzeit();
	void addSchueler();
	void addPlaetze();
	void addTeilleistung();
	void toggleFehlzeitenBewertung();
	void showFehlzeitenForSchueler();
	void showStundenbewertungenForSchueler();
	void writeFehlzeitenForSchueler();


protected:
    virtual QMenu* getPopupMenu();

private:
	SitzplanMapView *smapView;
	bool fehlzeitmode;
};

#endif
