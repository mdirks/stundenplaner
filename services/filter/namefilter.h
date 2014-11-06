//
// C++ Interface: namefilter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef NAMEFILTER_H
#define NAMEFILTER_H

#include "abstractfilter.h"

#include <string>

using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class NameFilter : public AbstractFilter {
public:
    NameFilter(string name);
    ~NameFilter();

     bool apply(PObject *o);

private:
	string name;
};

#endif
