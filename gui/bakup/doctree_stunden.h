//
// C++ Interface: doctree_stunden
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef DOCTREE_STUNDEN_H
#define DOCTREE_STUNDEN_H

#include <vector>

//#include <qdockwindow.h>
//#include <qlistbox.h>
#include <QWidget>
#include <QEvent>

#include "treestunden.h"
#include "pobjectlistbox.h"
#include "../persistence/database.h"

using namespace std;

/**
@author Marcus Dirks
*/
class doctree_stunden : public QWidget
{
Q_OBJECT

public:
    doctree_stunden(QWidget *parent);

    ~doctree_stunden();
    void readStunden();
    
private:
    PObjectListBox *listBox;

protected:
    void contentsMouseDoubleClickEvent(QMouseEvent *e);
    void contentsMousePressEvent(QMouseEvent *e);
public slots:
    void activateItem(QListBoxItem *item);
};

#endif
