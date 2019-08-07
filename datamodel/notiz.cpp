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
#include "notiz.h"
#include "notizmapper.h"

notiz::notiz()
{
	setMapper(notizmapper::getInstance());
}


notiz::~notiz()
{
}




/*!
    \fn notiz::getTitle()
 */
string notiz::getTitle()
{
    return this->title;
}


/*!
    \fn notiz::setTitle(string text)
 */
void notiz::setTitle(string text)
{
    this->title = text;
}


/*!
    \fn notiz::getBody()
 */
string notiz::getBody()
{
    return this->body;
}


/*!
    \fn notiz::setBody(string text)
 */
void notiz::setBody(string text)
{
    this->body = text;
}
