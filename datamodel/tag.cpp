//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "tag.h"
#include "tagmapper.h"

tag::tag()
{
	setMapper(tagmapper::getInstance());
}


tag::~tag()
{
}




/*!
    \fn tag::getDatum()
 */
QDate tag::getDatum()
{
    return this->date;
}


/*!
    \fn tag::setDatum(QDate &date);
 */
void tag::setDatum(QDate date)
{
    this->date = date;
}
