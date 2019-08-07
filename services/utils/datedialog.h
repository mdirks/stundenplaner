//
// C++ Interface: datedialog
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <qdialog.h>
#include <qpushbutton.h>
#include <kdatepicker.h>

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class DateDialog : public QDialog
{
Q_OBJECT

public:
    DateDialog();
    ~DateDialog();

    QDate date();

    static QDate getDate();

public slots:
	void dateSelected();

private:
	KDatePicker *datePicker;
	QPushButton *okButton;
};

#endif
