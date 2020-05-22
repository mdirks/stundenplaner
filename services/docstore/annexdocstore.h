#ifndef ANNEXDOCSTORE_H
#define ANNEXDOCSTORE_H

#include "docstore.h"
#include <QString>
#include <QFile>

class AnnexDocStore : public DocStore
{
public:
    AnnexDocStore(QString name, QString dir);

    static AnnexDocStore *getAnnexDocStore(QString name, QString dir);
    void init();
    void addRemote(){};

    bool addDocument(material *m);
    void removeDocument(QFile *file){};

    void getDocument(){};
    void dropDocument(){};
    void moveDocument(){};

    void setLocation(QString locationDirName) override;

    //QString getDirectory();

private:
    QString baseDir;
    QString storeName;
};

#endif // ANNEXDOCSTORE_H
