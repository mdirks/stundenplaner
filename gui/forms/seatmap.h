//
// C++ Interface: seatmap
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SEATMAP_H
#define SEATMAP_H

#include "datamodel/sitzplan.h"
#include "datamodel/klasse.h"
#include "gui/base/editrequestor.h"

#include <qwidget.h>
#include <map>

using namespace std;
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class SeatMap : public QWidget {

Q_OBJECT

public:
    SeatMap(int cols, int rows, QWidget *parent);
    SeatMap(sitzplan *sp, QWidget *parent);
    ~SeatMap();

public:
	EditRequestor *editRequestor;

public slots:
    void zeigeSchueler();

private:
	sitzplan *sp;
};

#endif
