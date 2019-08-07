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
#ifndef FORM_OPO_H
#define FORM_OPO_H

#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>

#include "../datamodel/opo.h"
#include "pobjectlistboxwidget.h"

/**
@author Marcus Dirks
*/
class form_opo : public QWidget
{
Q_OBJECT
public:
    form_opo(QWidget *parent = 0, const char *name = 0);
    ~form_opo();

    void setObject(opo *o);
    
    
private:
    QLabel *labelTitle;
    QLineEdit *editTitle;
    QPushButton *buttonSave;
    PObjectListBoxWidget *lbWidget;
    
    opo *o;
    
    
    
};

#endif
