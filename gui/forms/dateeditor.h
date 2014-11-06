//
// C++ Interface: dateeditor
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef DATEEDITOR_H
#define DATEEDITOR_H

#include "gui/base/propertyeditor.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/persistence/pobject.h"

#include <QDateTimeEdit>
#include <KDateWidget>

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class DateEditor : public KDateWidget /*QDateEdit*/, public PropertyEditor
{
Q_OBJECT

public:
    DateEditor(QWidget *parent);
    DateEditor(PObject *o, RepositoryProperty *prop, QWidget *p);

    ~DateEditor();
    void startEdit(RepositoryProperty *rp, PObject *parent);

public slots:
    void startEdit();
    void stopEdit();

private:
	RepositoryProperty *prop;
	PObject *parent;

};

#endif
