#include "collectionpropertyfilter.h"


CollectionPropertyFilter::CollectionPropertyFilter(RepositoryProperty *rp)
    : PropertyFilter(rp)
{

}

string CollectionPropertyFilter::getDisplayString()
{
    return PropertyFilter::getDisplayString() + "(Collection)";
}
