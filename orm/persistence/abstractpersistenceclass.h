/***************************************************************************
                          abstractpersistenceclass.h  -  description
                             -------------------
    begin                : Son Jul 20 2003
    copyright            : (C) 2003 by Marcus Dirks
    email                : marcus.dirks@t-online.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef ABSTRACTPERSISTENCECLASS_H
#define ABSTRACTPERSISTENCECLASS_H

#include "persistenceclass.h"
#include "pobject.h"

/**
  *@author Marcus Dirks
  */

class AbstractPersistenceClass : public PersistenceClass  {
public: 
   AbstractPersistenceClass();
	AbstractPersistenceClass(PObject *rs);
  virtual ~AbstractPersistenceClass();
private: // Private attributes
  /**  */
  PObject* realSubject;
  /** No descriptions */
public:
  virtual void save();
};

#endif
