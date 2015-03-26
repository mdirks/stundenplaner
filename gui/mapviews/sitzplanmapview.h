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
#ifndef SITZPLANMAPVIEW_H
#define SITZPLANMAPVIEW_H

#include "genericmapview.h"
#include "datamodel/stundenplaneintrag.h"
#include "datamodel/sitzplan.h"

#include "qwidget.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class SitzplanMapView : public GenericMapView {
Q_OBJECT
public:
    SitzplanMapView(SitzplanMap *spm, QWidget * parent = 0, const char * name = 0);
    ~SitzplanMapView();

    void setStundenplaneintrag(stundenplaneintrag *se);
    stundenplaneintrag* getStundenplaneintrag();
    void setFehlzeitenMode(bool fm){fehlzeitenmode=fm;};
    bool getFehlzeitenMode(){return fehlzeitenmode;}


    sitzplan* getSitzplan();
    SitzplanMap* getSitzplanMap();

public slots:
    void configure();

private:
	stundenplaneintrag *se;
	bool fehlzeitenmode;
};


class SitzplanMapViewDialog : public QWidget {
Q_OBJECT
public:
    SitzplanMapViewDialog(SitzplanMapView *spmv);
    SitzplanMapView* getMapView();
    void setStundenplaneintrag(stundenplaneintrag *se);

private:
    SitzplanMapView *mapView;

};

#endif
