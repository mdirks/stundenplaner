#ifndef MAPPINGEVENTSOURCE_H
#define MAPPINGEVENTSOURCE_H


#include <list>
#include <QString>

using namespace std;

class MappingEventListener;



class MappingEvent
{
public:
    MappingEvent(QString m){msg=m;};
    QString getMessage(){return msg;};
private:
    QString msg;
};




class MappingEventSource
{
public:
    MappingEventSource();

    void registerListener(MappingEventListener *listener);

protected:
    void publish(MappingEvent *me);

private:
    list<MappingEventListener*> *list_listener;
};



class VersionChangeRequest : public MappingEvent
{
   public:
    VersionChangeRequest(QString cName);

private:
    QString cName;
};

#endif // MAPPINGEVENTSOURCE_H
