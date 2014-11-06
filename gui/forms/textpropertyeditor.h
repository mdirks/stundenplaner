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
#ifndef TEXTPROPERTYEDITOR_H
#define TEXTPROPERTYEDITOR_H

#include <qtextedit.h>

#include "gui/base/propertyeditor.h"

/**
@author Marcus Dirks
*/
class TextPropertyEditor : public QTextEdit, public PropertyEditor
{
Q_OBJECT

public:
    TextPropertyEditor(QWidget *parent);
    TextPropertyEditor(PObject *o, QString displayString, QWidget *p);

    TextPropertyEditor(PObject *o, RepositoryProperty *prop, QWidget *p);
    ~TextPropertyEditor();
    
    void startEdit(RepositoryProperty *prop, PObject *o);
    void setParentObject(PObject *po);

public slots:
    void startEdit();
    void stopEdit();
    
    
private:
     PObject *parent;
     RepositoryProperty *property;
     bool editing;

protected:
    void focusOutEvent(QFocusEvent *e);
};

#endif
