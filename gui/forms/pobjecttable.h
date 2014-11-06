//
// C++ Interface: pobjecttable
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef POBJECTTABLE_H
#define POBJECTTABLE_H

#include <QString>
#include <QTableWidget>
#include <QMenu>
#include <QPixmap>

#include "abstractpropertyeditor.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/persistence/pobject.h"
#include "orm/mapping/abstractmapper.h"

#include <QObject>
#include <list>
#include <set>
#include <string>
#include <KDialog>

using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>

	Display a (homogenous) collection of PObjects
*/


class PObjectTableControler 
{
public:
	virtual void addElement(int row)=0;
        virtual QMenu* getContextMenu(const QPoint &pos)=0;

};






class PObjectTable : public QTableWidget , public AbstractPropertyEditor
 {
Q_OBJECT

public:
     PObjectTable(list<PObject*> *olist, QString type, QWidget *parent=0, bool addable=false);
	    
     PObjectTable(string className, QWidget *parent=0, bool addable=false);
     PObjectTable(AbstractMapper *mapper,QWidget *parent=0, bool addable=true);
     PObjectTable(RepositoryProperty *prop, PObject *parentObject, QWidget *parent=0, bool addable=true);

    ~PObjectTable();

	void stopEdit();
    	//void startEdit(RepositoryProperty *rp, PObject *parent);
    	void startEdit();
	void load();
	void createRow(int row, PObject *o);
        void startEdit(RepositoryProperty *rp, PObject *parent);
    	//void setControler(PObjectTableControler *controler);
	PObjectTableControler* getControler();
    AbstractMapper* getMapper();
    RepositoryProperty* getProperty();
    PObject* getParentObject();
    void startEdit(int row);
    void setDisplayProperties(list<RepositoryProperty*>* list_prop);
	PObject* getObject(int row);
	

public slots:
	void deleteSelected();
	void currentChanged(int row, int col);
	void valueChanged(int row, int col);
    void showContextMenu(const QPoint & pos );
	void load(list<PObject*>* olist);
	void loadType(string className);
	void removeRow(int row);

protected:
	void addElement(int row);
	
	void readRow(int row);
	void readPropertiesForType(string className);

private:
	QString clName, typedMimeType;
	RepositoryProperty *prop;
	PObject *parentObject;
    QMenu *pmenu;
	AbstractMapper *mapper;
	QPixmap icon;
	bool editing;

	//list<RepositoryProperty*> *propList;
	//list<PObject*> *objectList;
	QString teststring;
	PObjectTableControler *controler;
	set<int> set_editing;
	map<int,PObject*> map_obj;
	list<PObject*> *olist;
	map<int,RepositoryProperty*> map_prop;
	string typeName;

	bool addable;
    bool isloading;
	
};

class PObjectTableItem : public QTableWidgetItem
{
public:
    PObjectTableItem(QTableWidget * table);
    PObjectTableItem(PObject *o, QTableWidget * table);
	QWidget* createEditor() const;
	void setContentFromEditor(QWidget *w);
};

class PObjectTableControlerFactory
{
public:
	virtual PObjectTableControler* getControler(PObjectTable* table)=0;
	static PObjectTableControlerFactory* getInstance();
	static void setInstance(PObjectTableControlerFactory* instance);
private:
	static PObjectTableControlerFactory *instance;
};


class PObjectTableDialog : public KDialog
{
Q_OBJECT

public:
	PObjectTableDialog(list<PObject*> *data, string className,  QWidget *parent=0, bool addable=false);
	~PObjectTableDialog(){};

	static void edit(list<PObject*> *data, string className,bool addable=false);

private:
	PObjectTable *table;
};
#endif
