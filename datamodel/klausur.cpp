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
#include "klausur.h"

#include "klausurmapper.h"

klausur::klausur()
{
	list_noten=0;
	list_material=0;
	kl =0;
	setMapper(klausurmapper::getInstance());
}


klausur::~klausur()
{
}




/*!
    \fn klausur::getMaterialien()
 */
list<material*>* klausur::getMaterialien()
{
	if(list_material==0){
		list_material = klausurmapper::getInstance()->findMaterialien(getID());
	}
	return list_material;

}


/*!
    \fn klausur::addToMaterialien(material *m)
 */
void klausur::addToMaterialien(material *m)
{
    /// @todo implement me
}


/*!
    \fn klausur::deleteFromMaterialien(material *m)
 */
void klausur::deleteFromMaterialien(material *m)
{
    /// @todo implement me
}
