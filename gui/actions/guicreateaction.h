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
//#include "datamodel/stundenplantemplateeintrag.h"

#include <qobject.h>

#include <string>
#include <QStringList>
using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class GuiCreateAction : public QObject {

Q_OBJECT

public:
    GuiCreateAction();

    ~GuiCreateAction();
    static GuiCreateAction* getInstance();
    PObject*  create();
    static AbstractMapper* chooseMapper();
    static AbstractMapper* chooseMapper(QStringList classList);

    PObject* create(string className);
    void addStundenplaneintrag();

public slots:
	PObject*  createObject();
	PObject*  createObject(QStringList classList);

private:
	static GuiCreateAction *instance;
	AbstractMapper *mapper;
};

#endif
