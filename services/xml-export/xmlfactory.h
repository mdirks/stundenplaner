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
#ifndef XMLFACTORY_H
#define XMLFACTORY_H

#include <qstring.h>
#include <QDomElement>
#include <list>
#include <map>
#include "orm/persistence/pobject.h"

using namespace std;
/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class XmlFactory{
public:
    XmlFactory();
    ~XmlFactory();

    static XmlFactory *getInstance();

    void processFile(const QString fileName, list<PObject*> *results);
    PObject* readObjectElement(QDomElement objectElement);
    void exportObjectList(QString filename, list<PObject*> *objectList);
    

protected:
	void exportObjectList(QDomElement &parent, list<PObject*> *objectList);
	void exportObject(QDomElement &parent, PObject *o);
	QDomElement getTagForObject(PObject *o);

private:
    static XmlFactory *instance;
    QDomDocument  domDoc;
    map<int,int> exportMap;
    map<QString,PObject*> importMap;
};

#endif
