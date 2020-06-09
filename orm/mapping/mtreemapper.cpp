#include "mtreemapper.h"
#include "mtree.h"
#include "orm/repository/repositoryentryimpl.h"
#include "orm/repository/stringproperty.h"
#include "orm/repository/integerproperty.h"
#include "orm/repository/pobjectproperty.h"
#include "orm/repository/collectionpropertyimpl.h"
#include "orm/repository/numericproperty.h"
#include "orm/repository/dateproperty.h"
#include "orm/repository/booleanproperty.h"
#include "orm/repository/datetimeproperty.h"


MTreemapper* MTreemapper::instance=0;

MTreemapper* MTreemapper::getInstance()
{
   if(!instance){
       instance=new MTreemapper();
   }
   return instance;
}


MTreemapper::MTreemapper()
 {
   version = "0.2";
   columns = new string[0];
   columnTypes = new string[0];
   asc_Children = new Association<MTree, MTree>("mtree_mtree","mtree_p_id","mtree_ch_id","MTree", &MTree::addToChildren, &MTree::deleteFromChildren);
    mapAssociations["Children"] = asc_Children;
    registerAssociation( asc_Children);
    mapReferences["Parent"] = new Reference("MTree","MTree");
}


MTreemapper::~MTreemapper(){}


PObject* MTreemapper::createNewObject()
{
    return new MTree();
}


MTree* MTreemapper::create()
{
    return  (MTree*) AbstractMapper::create( MTreemapper::getInstance() );
}


string MTreemapper::getTableName()
{
    return string("mtree");
}

string MTreemapper::getClassName()
{
   return string("MTree");
}

string* MTreemapper::getColumnTypes()
{
   return columnTypes;
}

string* MTreemapper::getColumns()
{
   return columns;
}

int MTreemapper::getColumnCount()
{
    return 0;
}


string* MTreemapper::getValues(PObject *realSubject)
{
   string *values = new string[0];
   MTree *o = (MTree*) realSubject;
return values;
}


void MTreemapper::save(){
qWarning("MTree: save() not implemented");
}

void MTreemapper::save(PObject *realSubject)
{
   MTree *o = (MTree*) realSubject;

   Database *db = Database::getInstance();
   db->save(realSubject);
   asc_Children -> save(realSubject, o->getChildren() );
}


void MTreemapper::init(PObject* inito, Variant *res)
{
   MTree *o = (MTree*) inito;
   inito->init();
}


list<MTree *>*MTreemapper::find()
{
   return (list <MTree*>*) Database::getInstance()->getAll(this);
}


list<MTree*> * MTreemapper::findChildren(int pri_id)
{
   return asc_Children ->  findAssociates( pri_id );
    }


list<MTree*> * MTreemapper::findChildren(int pri_id,string prop,string value)
{
            return asc_Children ->  findAssociates( pri_id,prop,value);
}



RepositoryEntry* MTreemapper::getRepositoryEntry()
{
   RepositoryEntry* entry = new RepositoryEntryImpl( "MTree" );
   entry->addProperty( new StringProperty<MTree>("Name", "string", &MTree::getName, &MTree::setName, false) );
   entry->addProperty( new CollectionPropertyImpl<MTree,MTree>( "Children" , "MTree", &MTree::getChildren, &MTree::addToChildren, &MTree::deleteFromChildren  ) );
   entry->addProperty( new PObjectProperty<MTree,MTree>( "Parent" , "MTree", &MTree::getParent,&MTree::setParent ) );

   return entry;
}





