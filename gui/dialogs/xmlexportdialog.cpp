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
#include "xmlexportdialog.h"

#include "services/xml-export/xmlfactory.h"

#include "qfiledialog.h"
#include "qlayout.h"

XmlExportDialog::XmlExportDialog(QWidget *parent)
    : QDialog(parent )
{
	fileName = QString();

	QWidget *mainWidget = new QWidget(this);
	QVBoxLayout *la = new QVBoxLayout(mainWidget);

	
	iconView = new PObjectIconView(mainWidget);
	la->addWidget(iconView,10);


	labelFile = new QLabel(mainWidget);
	labelFile->setText("Exportieren nach: ");
	la->addWidget(labelFile);

    //ToDo: does it work without these?
    //setMainWidget(mainWidget);
    //setButtonText(User1,"File");
    //showButtonOK(false);
}


XmlExportDialog::~XmlExportDialog()
{
}

void XmlExportDialog::slotUser1()
{
    fileName = QFileDialog::getOpenFileName();
	if(fileName != QString()){
		labelFile->setText(QString("Exportieren nach: %1").arg(fileName));
        //showButtonOK(true);
	} else {

	}
    //QDialog::slotUser1();

}
void XmlExportDialog::slotOk()
{
	if(fileName != QString()){
		list<PObject*> *objectList = iconView->getObjectList();
		XmlFactory::getInstance()->exportObjectList(fileName, objectList);
       // QDialog::slotOk();
	} else {
		// do nothing because no file set
	}
}
