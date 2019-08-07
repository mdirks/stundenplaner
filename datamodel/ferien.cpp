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
#include "ferien.h"
#include "ferienmapper.h"

ferien::ferien()
{
	setMapper( ferienmapper::getInstance() );
}


ferien::~ferien()
{
}




/*!
    \fn ferien::getVon()
 */
QDate ferien::getVon()
{
    return von;
}


/*!
    \fn ferien::getBis()
 */
QDate ferien::getBis()
{
    return bis;
}


/*!
    \fn ferien::setBis(QDate date)
 */
void ferien::setBis(QDate date)
{
    bis=date;
}


/*!
    \fn ferien::setVon(QDate date)
 */
void ferien::setVon(QDate date)
{
    von=date;
}


/*!
    \fn ferien::getTitle()
 */
string ferien::getTitle()
{
    return title;
}


/*!
    \fn ferien::setTitle(string title)
 */
void ferien::setTitle(string title)
{
    this->title = title;
}
