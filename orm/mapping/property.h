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
#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

using namespace std;

/**
@author Marcus Dirks
*/
class Property{
public:
    Property(string prop);

    ~Property();
    string getString(int id);
    void set(string prop,int id);

private:
	string name;
};

#endif
