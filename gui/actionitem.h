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
#ifndef ACTIONITEM_H
#define ACTIONITEM_H

#include <QListWidgetItem>


/**
@author Marcus Dirks
*/
class ActionItem : public QListWidgetItem
{
public:
    ActionItem(QListWidgetItem *parent);
    ~ActionItem();
   

    virtual void actionPerformed() = 0;
    virtual int rtti() const;
    
public:
     static int Rtti;
};

#endif
