//
// C++ Interface: fileeditor
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include "gui/base/propertyeditor.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/persistence/pobject.h"

//#include <kurlrequester.h>

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class FileEditor : /*public KURLRequester ,*/ public PropertyEditor {
public:
    FileEditor(QWidget *parent);
    FileEditor(PObject *o, RepositoryProperty *prop, QWidget *p);
    ~FileEditor(){};


public slots:
    void startEdit();
    void stopEdit();

private:
	RepositoryProperty *prop;
	PObject *parent;

};

#endif
