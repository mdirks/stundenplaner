#include "mappingeventsource.h"

MappingEventSource::MappingEventSource()
{
    list_listener = new list<MappingEventListener*>();
}


void MappingEventSource::registerListener(MappingEventListener *listener)
{
    list_listener->push_back(listener);
}

VersionChangeRequest::VersionChangeRequest(QString className)
    : cName(className)
{

}
