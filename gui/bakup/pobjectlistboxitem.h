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
#ifndef POBJECTLISTBOXITEM_H
#define POBJECTLISTBOXITEM_H

#include <qlistbox.h>
#include "../persistence/pobject.h"

/**
@author Marcus Dirks
*/
class PObjectListBoxItem : public QListBoxItem
{
public:
    PObjectListBoxItem(PObject *o, QListBox *lb=0);

    ~PObjectListBoxItem();
    void paint(QPainter *p);
    int height(const QListBox *lb) const;
    int width(const QListBox *lb) const;
    PObject* getObject();

 private:
  	PObject *o;
};

#endif
