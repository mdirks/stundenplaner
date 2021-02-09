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
#ifndef ABSTRACTASSOCIATION_H
#define ABSTRACTASSOCIATION_H

#include <string>

#include "../persistence/pobject.h"

using namespace std;

//class AbstractMapper;

/**
@author Marcus Dirks
*/
class AbstractAssociation{

friend class MappingControler;
friend class AbstractMapper;

public:
    AbstractAssociation(const AbstractAssociation& asc);
    AbstractAssociation(string table,  string pri_col, string asc_col, string asc_class);

    virtual void deleteObject(PObject *o) = 0;
    string getAscClassName(){return asc_class;};

private:
    void createTable();
    void dropTable();

    
protected:  
     int pri_id;
     string table,  pri_col,  asc_col, asc_class;
     //AbstractMapper *typeMapper;
};

#endif
