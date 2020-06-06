#ifndef MAPPINGEVENTSOURCE_H
#define MAPPINGEVENTSOURCE_H


#include <list>
#include <QString>

using namespace std;

class MappingEventListener;

class MappingEventSource
{
public:
    MappingEventSource();

    void registerListener(MappingEventListener *listener);

private:
    list<MappingEventListener*> *list_listener;
};


class MappingEvent
{

};

class VersionChangeRequest : public MappingEvent
{
   public:
    VersionChangeRequest(QString className);

private:
    QString cName;
};

#endif // MAPPINGEVENTSOURCE_H
