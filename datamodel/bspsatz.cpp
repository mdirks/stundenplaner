#include "bspsatz.h"
#include "bspsatzmapper.h"

bspsatz::bspsatz()
{
    setMapper(bspsatzmapper::getInstance());
}
