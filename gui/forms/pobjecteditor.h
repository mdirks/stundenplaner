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
#ifndef POBJECTEDITOR_H
#define POBJECTEDITOR_H

#include <QWidget>
#include <QListWidgetItem>

#include "orm/persistence/pobject.h"
#include "textpropertyeditor.h"
#include "pobjectlistview.h"
#include "stringeditor.h"


/**
@author Marcus Dirks
*/
class PObjectEditor : public QWidget
{

Q_OBJECT

public:
    PObjectEditor( PObject *o, QWidget *parent=0);
    ~PObjectEditor();
  
public slots:
    void selectionChanged( QListWidgetItem *item);
   
private:
    PObject *rootObject;
    PObjectListView *listView;
    TextPropertyEditor *textEditor;
    PropertyEditor *activeEditor;
    StringEditor *stringEditor;

};

#endif
