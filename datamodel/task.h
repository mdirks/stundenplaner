//
// C++ Interface: task
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef TASK_H
#define TASK_H

#include <qdatetime.h>
#include "notizholder.h"
#include "orm/persistence/pobject.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class task : public notizholder {
public:
    task();
    ~task();

    QDate getDatum();
    void setDatum(QDate date);

    PObject* getBezugsobjekt();
    void setBezugsobjekt(PObject *r);

private:
	PObject *bo;
	QDate date;


};

#endif
