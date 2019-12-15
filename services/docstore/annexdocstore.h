#ifndef ANNEXDOCSTORE_H
#define ANNEXDOCSTORE_H

#include "docstore.h"
#include <QString>

class AnnexDocStore : public DocStore
{
public:
    AnnexDocStore();

    AnnexDocStore *createStore(QString name, QString dir);
    void addRemote();

    void addDocument();
    void removeDocument();

    void getDocument();
    void dropDocument();
    void moveDocument();

private:
    QString baseDir;
};

#endif // ANNEXDOCSTORE_H
