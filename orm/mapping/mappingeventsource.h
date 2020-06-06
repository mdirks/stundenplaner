#ifndef MAPPINGEVENTSOURCE_H
#define MAPPINGEVENTSOURCE_H


#include <list>
#include <QString>

using namespace std;

class MappingEventListener;



class MappingEvent
{
public:
    MappingEvent();
};




class MappingEventSource
{
public:
    MappingEventSource();

    void registerListener(MappingEventListener *listener);

private:
    void publish(MappingEvent *me);

private:
    list<MappingEventListener*> *list_listener;
};



class VersionChangeRequest : public MappingEvent
{
   public:
    VersionChangeRequest(QString className);

private:
    QString cName;
};

#endif // MAPPINGEVENTSOURCE_H
