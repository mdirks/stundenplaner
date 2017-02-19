/***************************************************************************
 *   Copyright (C) 2008 by Marcus Dirks   *
 *   m-dirks@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "xmlimportdialog.h"

#include "qlayout.h"
#include "qlabel.h"
#include "qstring.h"
#include <list>
#include <qfiledialog.h>

#include "orm/persistence/pobject.h"
#include "gui/forms/pobjecticonview.h"
#include "services/xml-export/xmlfactory.h"

using namespace std;

XmlImportDialog::XmlImportDialog(QWidget *parent)
    : QDialog(parent)
{
// 	QWidget *page = new QWidget( this );
//    	setMainWidget(page);
// 	QVBoxLayout *topLayout = new QVBoxLayout( page, 0, spacingHint() );
// 	
// 	 QLabel *label = new QLabel( QString("Import-File"), page, "caption" );
//    	 topLayout->addWidget( label ,10);
// 
// 	PObjectIconView *iconView = new PObjectIconView(this);
// 	topLayout-> addWidget( iconView,90);

	iconView = new PObjectIconView(this);
    //ToDo: does chooser show up, add to layout ?
    //setMainWidget(iconView);

	 
}


XmlImportDialog::~XmlImportDialog()
{
}

void XmlImportDialog::slotUser1()
{
	qDebug("User 1 pressed");
    QString filename = QFileDialog::getOpenFileName();
	list<PObject*> *results = new list<PObject*>();
	XmlFactory::getInstance()->processFile(filename, results);
	iconView->load(results);
    //QDialog::slotUser1();
}
