#ifndef URLPROPERTY_H
#define URLPROPERTY_H

#include "repositorypropertyimpl.h"
#include "orm/mapping/murl.h"

template<class ObjectType> class UrlProperty : public RepositoryPropertyImpl
{
    typedef MUrl (ObjectType::*urlgetter)();
    typedef void (ObjectType::*urlsetter)(MUrl url);


    public:
        UrlProperty(string name, string type, urlgetter g, urlsetter s=0)
            : RepositoryPropertyImpl(name, type){getter = g; setter = s;} ;

        ~UrlProperty();

            MUrl asUrl(PObject *parent);
            string asString(PObject *parent);
            void fromString(string st, PObject *parent);

        bool isUrl(){return true;}

    private:
            urlgetter getter;
            urlsetter setter;
};

     template<class ObjectType>
    MUrl UrlProperty<ObjectType>::asUrl(PObject *parent)
    {
        ObjectType *ot = dynamic_cast<ObjectType*>(parent);
        if(ot){
                return (ot->*getter)();
        } else {
            qDebug("Warning: Wrong parent type in UrlProperty: returning nonsensical url");
            return MUrl("Nonsense");
        }
    }


    template<class ObjectType>
    string UrlProperty<ObjectType>::asString(PObject *o)
    {
        ObjectType *ot = dynamic_cast<ObjectType*>(o);
        if(ot){
            MUrl u=(ot->*getter)();
            return u.toStdString();
        } else {
            return string("Conversion failed due to wrong object type");
        }
    }

    template<class ObjectType>
    void UrlProperty<ObjectType>::fromString(string text, PObject *o)
    {
            ObjectType *ot = dynamic_cast<ObjectType*>(o);
            if(ot){
                    if(setter){
                        MUrl u(text);
                        (ot->*setter)(u);
                    } else {
                            qDebug("Failed to set property: setter not provided");
                    }
            } else {
                    qDebug("Conversion failed due to wrong object type");
             }

    }


#endif // URLPROPERTY_H
