/***************************************************************************
                          opo.h  -  description
                             -------------------
    begin                : Sam Feb 28 2004
    copyright            : (C) 2004 by Marcus Dirks
    email                : marcus.dirks@web.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef OPO_H
#define OPO_H

#include <list>
#include <string>

//#include <qstring.h>

#include "material.h"
#include "orm/transactions/transactionobject.h"
#include "orm/persistence/pobject.h"

using namespace std;

/**
  *@author Marcus Dirks
  */

class opo : public TransactionObject
{
public: 
	opo();
	~opo();
  
       void setTitle(string title);
      string getTitle();
     
      list<material*> *getMaterialien();
      void addToMaterialien(material *ma);
      void deleteFromMaterialien(material *ma);
      
  
private: // Private attributes
   string title;
   list<material*> *list_materialien;
};

#endif
