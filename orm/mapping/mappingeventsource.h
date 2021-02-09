#ifndef MAPPINGEVENTSOURCE_H
#define MAPPINGEVENTSOURCE_H

#include "mappingeventlistener.h"
#include <string>
#include <list>
#include <set>

using namespace std;

class MappingEventSource
{
public:
    MappingEventSource();
    void addMappingEventListener(MappingEventListener *listener);
    bool requestVersionChange(string className);
    bool ask(string req);
    void report(string rep);

private:
    //list<MappingEventListener*> *m_listListener;
    set<MappingEventListener*> *m_listListener;
};

#endif // MAPPINGEVENTSOURCE_H
