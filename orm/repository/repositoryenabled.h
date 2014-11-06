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
#ifndef REPOSITORYENABLED_H
#define REPOSITORYENABLED_H

#include "repositoryentry.h"

/**
@author Marcus Dirks
*/
class RepositoryEnabled{
public:
    
    virtual RepositoryEntry* getRepositoryEntry() = 0;

};

#endif
