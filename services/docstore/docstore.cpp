#include "docstore.h"
#include "annexdocstore.h"
#include <QDir>

#define DIR "/data3/mopp/stundenplaner"
#define NAME "Docstore"

DocStore* DocStore::instance=0;


DocStore* DocStore::getInstance()
{
    if(instance==0){
        instance=AnnexDocStore::getAnnexDocStore(NAME,DIR);
    }
    return instance;
}


QString DocStore::getDirectory()
{
    return QString(DIR).append("/").append(NAME);
}

DocStore::DocStore()
{

}
