#include "testpcollection.h"
#include "services/actions/createaction.h"
#include "orm/persistence/pcollection.h"

TestPCollection::TestPCollection()
    : TestCase()
{

}

void TestPCollection::run()
{
    PObject *o=CreateAction::getInstance()->create("PCollection");
    if(!o) fail("Unable to create PCollection");
    PCollection *po = (PCollection*) o;
    if(!po) fail("Created object has  wrong type");
}
