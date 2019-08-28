/***************************************************************************
                          repository.h  -  description
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

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <map>
#include <unordered_map>
//#include <hash_map>
//#include <ext/hash_map>
#include <string>


#include "repositoryentry.h"
#include "../persistence/pobject.h"
#include "../services/filter/filter.h"

/**
  *@author Marcus Dirks
  */

#include <string>
using namespace std;
//using namespace __gnu_cxx;

/*
struct equal_char {

	bool operator() (const char* c1, const char* c2){
   		return strcmp(c1,c2) == 0;
	}

};
*/


class strless {
   public:
      bool operator() (const string & first, const string & second ) const  {
         return first < second;
      }
};


//typedef  /*hash_map*/map<const char*, RepositoryEntry*, /*hash<const char*>,*/equal_char> entrymap;
typedef  /*hash_map*/std::map<std::string, RepositoryEntry*, /*hash<const char*>,*/strless> entrymap;
//typedef  hash_map<const char*, RepositoryEntry> entrymap;

class Repository {
public: 
	
	static Repository* getInstance();
	
	RepositoryEntry* getRepositoryEntry(string className);
	void addRepositoryEntry(RepositoryEntry* entry);
	
public:	
		Repository();
	~Repository();
    RepositoryEntry* getRepositoryEntry(PObject* o);

		
public:
	entrymap classNameToRe;	
	static Repository* instance;
};



#endif
