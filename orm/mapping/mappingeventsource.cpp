#include "mappingeventsource.h"

MappingEventSource::MappingEventSource()
{
    //m_listListener = new list<MappingEventListener*>();
    m_listListener = new set<MappingEventListener*>();
}

void MappingEventSource::addMappingEventListener(MappingEventListener *listener)
{
    //m_listListener->push_back(listener);
    m_listListener->insert(listener);
}

bool MappingEventSource::ask(string req)
{
    bool conf=true;
    for(set<MappingEventListener*>::iterator it = m_listListener->begin(); it!= m_listListener->end(); it++){
            conf = conf & (*it)->confirm(req);
    }
    return conf;
}

bool MappingEventSource::requestVersionChange(string className)
{
    bool doversionchange=true;
    for(set<MappingEventListener*>::iterator it = m_listListener->begin(); it!= m_listListener->end(); it++){
                doversionchange = doversionchange & (*it)->versionChangeRequested(className);
    }
    return doversionchange;
}


void MappingEventSource::report(string rep)
{
    for(set<MappingEventListener*>::iterator it = m_listListener->begin(); it!= m_listListener->end(); it++){
                (*it)->message(rep);
    }
}
