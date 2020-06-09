#ifndef MTREEMAPPER_H
#define MTREEMAPPER_H

#include "mtree.h"
#include "abstractmapper.h"
#include "repository/repositoryenabled.h"
#include "orm/mapping/association.h"

class MTreemapper : public AbstractMapper, public RepositoryEnabled
{
public:
    static MTreemapper* getInstance();
    ~MTreemapper();
    static MTree* create();

    string getTableName();
    string getClassName();
    string* getColumnTypes();
    string* getColumns();
    string* getValues(PObject* realSubject);
    int getColumnCount();
    void save();
    void save(PObject *realSubject);
    PObject* createNewObject();
    list<MTree*>* find();
   void init(PObject* o, Variant* res);
   RepositoryEntry *getRepositoryEntry();

    MTree * findParent(int pri_id);
    list<MTree*> * findChildren(int pri_id);
    list<MTree*> * findChildren(int pri_id,string prop,string value);

protected:
    MTreemapper();

private:
   static MTreemapper* instance;

   Association<MTree, MTree> *asc_Children;

  string *columnTypes;
   string *columns;

};

#endif // MTREEMAPPER_H
