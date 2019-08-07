/****************************************************************************
** Form implementation generated from reading ui file 'form_stunde_rt.ui'
**
** Created: Die Apr 12 18:07:54 2005
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "form1.h"

#include <qvariant.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a Form1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
Form1::Form1( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "Form1" );
    resize( 406, 476 ); 
    setCaption( trUtf8( "Form1" ) );

    GroupOpo = new QGroupBox( this, "GroupOpo" );
    GroupOpo->setGeometry( QRect( 10, 50, 381, 171 ) ); 
    GroupOpo->setTitle( trUtf8( "Opos" ) );

    buttonNewOpo = new QPushButton( GroupOpo, "buttonNewOpo" );
    buttonNewOpo->setGeometry( QRect( 240, 140, 131, 21 ) ); 
    buttonNewOpo->setText( trUtf8( "Neues Opo" ) );

    listBoxOpos = new QListBox( GroupOpo, "listBoxOpos" );
    listBoxOpos->insertItem( trUtf8( "New Item" ) );
    listBoxOpos->setGeometry( QRect( 20, 30, 341, 71 ) ); 

    editThema = new QLineEdit( this, "editThema" );
    editThema->setGeometry( QRect( 91, 10, 300, 22 ) ); 

    labelThema = new QLabel( this, "labelThema" );
    labelThema->setGeometry( QRect( 10, 10, 70, 21 ) ); 
    labelThema->setText( trUtf8( "Thema" ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
Form1::~Form1()
{
    // no need to delete child widgets, Qt does it all for us
}

