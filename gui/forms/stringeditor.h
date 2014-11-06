//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STRINGEDITOR_H
#define STRINGEDITOR_H

#include <qlineedit.h>
#include <qstring.h>
#include "abstractpropertyeditor.h"
/**
@author Marcus Dirks
*/
class StringEditor : public QLineEdit, public AbstractPropertyEditor
{
Q_OBJECT

public:
    StringEditor(QWidget *parent);
    StringEditor(PObject *o, RepositoryProperty *prop, QWidget *p);
    ~StringEditor(){};
    
    void startEdit(RepositoryProperty *prop, PObject *o);

public slots:
    void startEdit(const QString &text);
    void stopEdit();
    void startEdit();
    
private:
     PObject *parent;
     RepositoryProperty *property;
     bool editing;
    
};

#endif
