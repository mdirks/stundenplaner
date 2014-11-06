/***************************************************************************
                          stunde.h  -  description
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

#ifndef STUNDE_H
#define STUNDE_H

#include <list>

#include <qstring.h>
#include "material.h"
#include "opo.h"
#include "ziel.h"
#include "orm/transactions/transactionobject.h"
#include "orm/persistence/pobject.h"
#include "orm/persistence/pcollection.h"
//#include "../orm/mappingstundemapper.h"
#include "thema.h"
#include "notizholder.h"

using namespace std;

/**
  *@author Marcus Dirks
  */

  
class stunde : /*public TransactionObject,*/ public notizholder {

friend class stundepersistence;

public: 
    //static stundemapper* getMapper(){return stundemapper::getInstance();};


	stunde();
	~stunde();
  /** No descriptions */
  thema* getThema();
  /** No descriptions */
  string getZielAsString();
  /** No descriptions */
  string getOpoAsString();
  /** No descriptions */
  //QString toQString();
  
  list<opo*>* getOpos();
  void addToOpos(opo *o);
  void deleteFromOpos(opo *o);

   list<material*> *getMaterialien();
      void addToMaterialien(material *ma);
      void deleteFromMaterialien(material *ma);


  string toString();
    void setThema(thema  *th);
    string getVerlauf();
    void setVerlauf(string verlauf);
    string getTitle();
    void setTitle(string t);
    
    //void setOpos(PCollection *col);

private: // Private attributes
  /**  */
  thema *th;
  /**  */
  list<opo*> *list_opos;
  list<material*> *list_materialien;
  /**  */
  list <ziel*> list_ziele;
  /**  */
  string str_rep;
  
  string title, verlauf;
};

#endif
