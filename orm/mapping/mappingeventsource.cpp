#include "mappingeventsource.h"
#include "mappingeventlistener.h"

MappingEventSource::MappingEventSource()
{
    list_listener = new list<MappingEventListener*>();
}


void MappingEventSource::registerListener(MappingEventListener *listener)
{
    list_listener->push_back(listener);
}

void MappingEventSource::publish(MappingEvent *me)
{
    for(list<MappingEventListener*>::iterator it=list_listener->begin(); it!=list_listener->end(); it++){
        MappingEventListener *l = (*it);
        l->consider(me);

    }
}

VersionChangeRequest::VersionChangeRequest(QString className)
    : MappingEvent(QString("Versionswechsel erforderlich für %1").arg(className)),
      cName(className)
{

}
