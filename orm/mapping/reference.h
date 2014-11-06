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
#ifndef REFERENCE_H
#define REFERENCE_H

#include <string>

#include "mappedobject.h"
#include "../persistence/pobject.h"

using namespace std;
/**
@author Marcus Dirks
*/
class Reference{
public:
    Reference(const Reference &ref);
    Reference(string table, string pri_col, string ref_col, string ref_class);
    Reference(string pri_class, string ref_class);
    Reference(string pri_class, string ref_class, string ref_name);
    ~Reference();
    
    void createTable();
    PObject *findReferee(int pri_id);
    void deleteReferee(int pri_id);
    void save(PObject *realSubject, PObject *refSubject);
    
private:
    string table, pri_col, ref_col,  ref_class;

};

#endif
