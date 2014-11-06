/****************************************************************************
** Form interface generated from reading ui file 'treestunden.ui'
**
** Created: Die Mär 22 17:03:35 2005
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef TREESTUNDEN_H
#define TREESTUNDEN_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QListView;
class QListViewItem;

class TreeStunden : public QWidget
{ 
    Q_OBJECT

public:
    TreeStunden( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~TreeStunden();

    QListView* ListView1;


protected:
    QVBoxLayout* TreeStundenLayout;
};

#endif // TREESTUNDEN_H
