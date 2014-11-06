//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REPOSITORYENTRYIMPL_H
#define REPOSITORYENTRYIMPL_H

#include "repository.h"
#include "repositoryentry.h"
#include <ext/hash_map>
#include <string>

using namespace std;
using namespace __gnu_cxx;
/**
@author Marcus Dirks
*/
class RepositoryEntryImpl : public RepositoryEntry {

typedef  hash_map<const char*, RepositoryProperty*, hash<const char*>,equal_char> propertymap;

public:
    RepositoryEntryImpl(const string &className);
    ~RepositoryEntryImpl();
    void addProperty(RepositoryProperty *p);
    RepositoryProperty* getProperty(string name);
    string getClassName();
    list<RepositoryProperty*> * getAllProperties(bool withBase = false);
    void registerBase(string baseClassName);
    RepositoryProperty* getMainProperty();
    string getBaseClassName();
    
private:
	propertymap nameToFunc;
        list<RepositoryProperty*> *allProperties, *allProperties_withBase;
	string className, baseClassName;
	bool hasBase;
	RepositoryProperty *mprop;
};

#endif
