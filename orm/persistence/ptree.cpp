#include "ptree.h"

PTree::PTree()
{
    setPersistenceObject(PTreePersistence::getInstance());
}
