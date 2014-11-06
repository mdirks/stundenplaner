/****************************************************************************
** Form interface generated from reading ui file './treetab.ui'
**
** Created: Do Sep 4 20:35:29 2008
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef TREETAB_H
#define TREETAB_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;

class TreeTab : public QWidget
{
    Q_OBJECT

public:
    TreeTab( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~TreeTab();

    QTabWidget* mainTab;
    QWidget* tab;
    QWidget* tab_2;

protected:

protected slots:
    virtual void languageChange();

};

#endif // TREETAB_H
