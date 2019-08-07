//
// C++ Implementation: datedialog
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "datedialog.h"
#include <qlayout.h>
#include <qpushbutton.h>
#include <QDialog>

DateDialog::DateDialog()
    : QDialog()
{
	setMinimumSize(400,500);
	QVBoxLayout *l = new QVBoxLayout(this);
	
	datePicker = new KDatePicker(this);
	l->addWidget(datePicker,90);
	okButton = new QPushButton("OK",this);
	l->addWidget(okButton);
	
	connect(okButton, SIGNAL(pressed()), this, SLOT(accept( )));
}


DateDialog::~DateDialog()
{
}

QDate DateDialog::date()
{
	return datePicker->date();
}

QDate DateDialog::getDate()
{
	DateDialog *d= new DateDialog();
	d->exec();

	return d->date();
}

void DateDialog::dateSelected(  ){
	
}
