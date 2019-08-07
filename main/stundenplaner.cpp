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


#include "stundenplaner.h"

#include <QLabel>
#include <QDebug>

#include <kmainwindow.h>
//#include <klocale.h>

stundenplaner::stundenplaner()
    : KMainWindow(   )
{
    // set the shell's ui resource file
    //setXMLFile("stundenplanerui.rc");

    //new QLabel( "Hello World", this, "hello label" );
    qDebug() << "stundenplaner() : What should we do here?";
}


stundenplaner::~stundenplaner()
{
}

//#include "stundenplaner.moc"
