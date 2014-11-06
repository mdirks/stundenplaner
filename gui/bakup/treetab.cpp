#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './treetab.ui'
**
** Created: Do Sep 4 20:37:41 2008
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "treetab.h"

#include <qvariant.h>
#include <qtabwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a TreeTab as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
TreeTab::TreeTab( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "TreeTab" );

    mainTab = new QTabWidget( this, "mainTab" );
    mainTab->setGeometry( QRect( 0, 0, 510, 490 ) );
    mainTab->setTabPosition( QTabWidget::Bottom );

    tab = new QWidget( mainTab, "tab" );
    mainTab->insertTab( tab, QString::fromLatin1("") );

    tab_2 = new QWidget( mainTab, "tab_2" );
    mainTab->insertTab( tab_2, QString::fromLatin1("") );
    languageChange();
    resize( QSize(604, 480).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
TreeTab::~TreeTab()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void TreeTab::languageChange()
{
    setCaption( tr2i18n( "Selection" ) );
    mainTab->changeTab( tab, tr2i18n( "Tab 1" ) );
    mainTab->changeTab( tab_2, tr2i18n( "Tab 2" ) );
}

#include "treetab.moc"
