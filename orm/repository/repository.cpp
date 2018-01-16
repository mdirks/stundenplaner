/***************************************************************************
                          repository.cpp  -  description
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

#include "repository.h"


#include "services/utils/utils.h"
#include <QDebug>




Repository::Repository(){

}
Repository::~Repository(){
}

Repository* Repository::instance;

Repository* Repository::getInstance(){
	if(!Repository::instance){
		Repository::instance = new Repository();
	}
	return Repository::instance;
}


RepositoryEntry* Repository::getRepositoryEntry(string className){

   /*
    RepositoryEntry *re=classNameToRe[className.c_str()];
   if(re){
       return re;
   }else{
       qDebug() << "ClassName " << className.c_str() << "Not found in map";
           return 0;
   }
   */
    unordered_map<std::string,RepositoryEntry*>::iterator it  = classNameToRe.find(className);
   //unordered_map<const char*,RepositoryEntry*>::iterator it  = classNameToRe.find(className);
   //unordered_map<const char*,RepositoryEntry*, hash<const char*>,equal_char>::iterator it  = classNameToRe.find(className.c_str());
   //hash_map<const char*,RepositoryEntry*, hash<const char*>,equal_char>::iterator it  = classNameToRe.find(className.c_str());
   if(it != classNameToRe.end()){
       return it->second;
	}else {
        qDebug() << "ClassName " << className.c_str() << "Not found in map";
      		return 0;
	}

}

void Repository::addRepositoryEntry(RepositoryEntry* entry){
   if(!entry){
       qDebug() << "TROUBLE given entry is 0";
   }
   string className = entry->getClassName();
   qDebug() << QString("Added: ").append(className.c_str());
    classNameToRe[className] = entry;
}


/*!
    \fn Repository::getRepositoryEntry(MappedObject* o)
 */
RepositoryEntry* Repository::getRepositoryEntry(PObject* o)
{
    string classname = o->getPersistenceObject()->getClassName();
    return getRepositoryEntry(classname);
}
