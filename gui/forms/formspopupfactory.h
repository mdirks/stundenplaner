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
#ifndef FORMSPOPUPFACTORY_H
#define FORMSPOPUPFACTORY_H

#include <QMenu>
#include "gui/forms/pobjecticonview.h"
#include "gui/forms/pobjecttable.h"
#include "gui/forms/pobjectmultiview.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class FormsPopupFactory{
public:
    
    virtual QMenu* getPopupFor(PObjectIconView  *iconView) = 0;
    virtual QMenu* getPopupFor(PObjectTable  *iconView) = 0;
    virtual QMenu* getPopupFor(PObjectMultiView  *iconView) = 0;

    static FormsPopupFactory* getInstance();
    static void setInstance(FormsPopupFactory *factory);

private:
	static FormsPopupFactory* instance;


};

#endif
