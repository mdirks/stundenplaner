/****************************************************************************
** Form interface generated from reading ui file 'form_stunde_rt.ui'
**
** Created: Die Apr 12 18:07:54 2005
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FORM1_H
#define FORM1_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QGroupBox;
class QLabel;
class QLineEdit;
class QListBox;
class QListBoxItem;
class QPushButton;

class Form1 : public QWidget
{ 
    Q_OBJECT

public:
    Form1( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Form1();

    QGroupBox* GroupOpo;
    QPushButton* buttonNewOpo;
    QListBox* listBoxOpos;
    QLineEdit* editThema;
    QLabel* labelThema;


};

#endif // FORM1_H
