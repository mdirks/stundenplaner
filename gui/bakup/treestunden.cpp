/****************************************************************************
** Form implementation generated from reading ui file 'treestunden.ui'
**
** Created: Die Mär 22 17:03:36 2005
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "treestunden.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>


/* 
 *  Constructs a TreeStunden which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
TreeStunden::TreeStunden( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "TreeStunden" );
    resize( 280, 480 ); 
    setCaption( trUtf8( "Form1" ) );
    TreeStundenLayout = new QVBoxLayout( this, 11, 6, "TreeStundenLayout"); 

    ListView1 = new QListView( this, "ListView1" );
    ListView1->addColumn( trUtf8( "Column 1" ) );
    QListViewItem * item = new QListViewItem( ListView1, 0 );
    item->setText( 0, trUtf8( "New Item" ) );

    TreeStundenLayout->addWidget( ListView1 );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
TreeStunden::~TreeStunden()
{
    // no need to delete child widgets, Qt does it all for us
}

