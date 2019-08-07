//
// C++ Interface: createaction
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef CREATEACTION_H
#define CREATEACTION_H

#include  "orm/mapping/abstractmapper.h"
#include "orm/persistence/pobject.h"

#include <qobject.h>

#include <string>

using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class CreateAction : public QObject {

Q_OBJECT

public:
    CreateAction();

    ~CreateAction();
    static CreateAction* getInstance();
    //PObject*  create();
    //static AbstractMapper* chooseMapper();
    PObject* create(string className);

public slots:
	//PObject*  createObject();

private:
	static CreateAction *instance;
	AbstractMapper *mapper;
};

#endif
