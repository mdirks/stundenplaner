/***************************************************************************
                          repositoryentry.h  -  description
                             -------------------
    begin                : Sun Oct 6 2002
    copyright            : (C) 2002 by Marcus Dirks
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

#ifndef REPOSITORYENTRY_H
#define REPOSITORYENTRY_H
                         
#include <string>
#include <map>

#include "repositoryproperty.h"

/**
  *@author Marcus Dirks
  */

class RepositoryEntry {
public: 
	RepositoryEntry(){};
	virtual ~RepositoryEntry(){};

	virtual RepositoryProperty* getProperty(string name)=0;
        virtual void addProperty(RepositoryProperty *p) = 0;
        virtual string getClassName()=0;
        virtual list<RepositoryProperty*> * getAllProperties(bool withBase=false)=0;
    virtual void registerBase(string baseClassName) = 0;
    virtual RepositoryProperty* getMainProperty()=0;
    virtual string getBaseClassName() = 0;


	//void addProperty(string name, RepositoryProperty* rp);
	
private:
	//map<string,RepositoryProperty*> nameToRp;
	
};

#endif
