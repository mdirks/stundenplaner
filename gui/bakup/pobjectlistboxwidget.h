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
#ifndef POBJECTLISTBOXWIDGET_H
#define POBJECTLISTBOXWIDGET_H

#include <qwidget.h>
#include <qpushbutton.h>

#include "pobjectlistbox.h"

/**
@author Marcus Dirks
*/
class PObjectListBoxWidget : public QWidget
{
Q_OBJECT
public:
    PObjectListBoxWidget(QWidget *parent = 0, const char *name = 0);
    ~PObjectListBoxWidget();

    PObjectListBox *listBox;
    
private:
    QPushButton *buttonNew, *buttonDelete;
    
};

#endif
