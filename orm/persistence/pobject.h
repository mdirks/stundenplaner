/***************************************************************************
                          pobject.h  -  description
                             -------------------
    begin                : Fri Oct 4 2002
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

#ifndef POBJECT_H
#define POBJECT_H

#include <string>

#include "persistenceclass.h"

/**
  *@author Marcus Dirks
  */

using namespace std;

class PersistenceClass;
  
class PObject {
public: 
	PObject();
	virtual ~PObject();
	
  	virtual string getName();
	virtual void setName(string name);
  	
	virtual string toString();
  

 	 PersistenceClass  *getPersistenceObject();
  
  	int getID();
  	void setID(int id);
  
  	virtual void save();
	virtual void deleteObject();
	
        bool isSaved();
	
	virtual void init(){};
    string getClassName();
    bool getRemoved();
    void setRemoved(bool removed);

protected:
	void setPersistenceObject(PersistenceClass *persObj);
    
    	
	PersistenceClass* persObj;
	
private:
	int id;
	string name;
	
protected:
    bool saved;
    bool removed;
};

#endif
