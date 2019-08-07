//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef TAG_H
#define TAG_H

#include "notizholder.h"
#include <qdatetime.h>

/**
@author Marcus Dirks
*/
class tag : public notizholder
{
public:

    tag();
    ~tag();
    QDate getDatum();
    void setDatum(QDate date);;

private:
	QDate date;

};

#endif
