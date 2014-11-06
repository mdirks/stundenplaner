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
#ifndef POBJECTLISTBOX_H
#define POBJECTLISTBOX_H

#include "pobjectpopupmenu.h"
#include "../persistence/pobject.h"
#include <qlistbox.h>
#include <list>

using namespace std;

/**
@author Marcus Dirks
*/
class PObjectListBox : public QListBox
{
public:
    PObjectListBox(QWidget *parent=0, const char *name=0);

    ~PObjectListBox();
    void insertItem(PObject *o);
    void addObjects(list<PObject*> *);

private:
    PObjectPopupMenu *popupMenu;
};

#endif
