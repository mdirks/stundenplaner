#ifndef COLLECTIONPROPERTYFILTER_H
#define COLLECTIONPROPERTYFILTER_H

#include "propertyfilter.h"

class CollectionPropertyFilter : public PropertyFilter
{
public:
    CollectionPropertyFilter(RepositoryProperty *rp);
    string getDisplayString();
};

#endif // COLLECTIONPROPERTYFILTER_H
