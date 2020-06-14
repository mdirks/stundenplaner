//
// C++ Interface: pobjecticonview
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef POBJECTICONVIEW_H
#define POBJECTICONVIEW_H

#include <QListWidget>
#include <QPixmap>
#include <QMenu>
#include "../orm/mapping/abstractmapper.h"
#include "gui/draganddrop/pobjectdata.h"
#include "pobjecticonviewitem.h"
#include "gui/base/propertyeditor.h"
#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryproperty.h"
#include "services/filter/filter.h"
#include "pobjecttable.h"
#include "gui/draganddrop/pobjectdroptarget.h"
#include "gui/forms/pobjectlistprovider.h"


//#include <kiconview.h>
//#include <kxmlguiclient.h>
//#include <kaction.h>
//#include <kaccel.h>

#include <list>
#include <string>

using namespace std;


/**   Shows an IconView for a PObject collection

	Offers appropriate PopupMenus

	Two modie are implemented and can be selected by calling the corresponding constructor

		- 	Show all objects in the system of a given type. 
				This is done using the corresponding mappers  find_gen() method.

		- 	Show the contents of a CollectionProperty for some object
				This is done using the Properties  \code asCollection( parentObject ) \endcode method



	@author Marcus Dirks <marcus.dirks@web.de>
*/
class PObjectIconView : public QListWidget, /*public KXMLGUIClient,*/ public PropertyEditor, public PObjectDropTarget
{
Q_OBJECT

public:
    PObjectIconView(QWidget *parent=0);
    PObjectIconView(PObjectListProvider *prov, QWidget *parent=0);
	PObjectIconView(list<PObject*> *olist, QWidget *parent=0);
    PObjectIconView(AbstractMapper *mapper, QWidget *parent=0);
    PObjectIconView(QString className, QWidget *parent=0);
    	PObjectIconView(RepositoryProperty *prop, PObject *parentObject, QWidget *parent=0);

    	~PObjectIconView();
    	void load();
   	void load(list<PObject*>* olist);
   	void addObject(PObject *o);
	void deleteObject(PObjectIconViewItem *item);

	void stopEdit();
    void startEdit(RepositoryProperty *rp, PObject *parent);
    void startEdit();

    QMenu* getPopupMenu();
    list<PObject*>* getObjectList();
    //AbstractMapper* getMapper();

    //void setMapper(AbstractMapper *mapper);
	PObject* getSelected();
    PObject* getCurrent();

    virtual void 	startDrag ( Qt::DropActions supportedActions );
    void setTableView(PObjectTable *table);
    PObjectTable* getTableView();



    void setDisplayProperty(RepositoryProperty *p);
    void setDisplayProperties(list<RepositoryProperty*> *listRp);
    void setObjectListProvider(PObjectListProvider *prov);
    PObjectListProvider* getProvider();

    void setFilter(Filter *f);
    void clearFilter();

protected:
	//QPopupMenu*  getDatenPopupForSelected();
private:
	AbstractMapper *mapper;
	QPixmap icon;
	bool editing;
	list<PObject*> *olist;
    PObjectTable *tableView;
    list<RepositoryProperty*> *displayPropList;

public slots:
    void activateItem(QListWidgetItem *item);
    void changeCurrent(QListWidgetItem *current,QListWidgetItem *previous);
    void reload();
    //void newIconView();
    //void configureView();
    void renameObject(QListWidgetItem* item);
    PObjectIconViewItemBase* createItem(PObject* o);
    //void selectIcon();
    void selectFile();

    void show();
    void chooseFilter();
    void paste();
    //void copy();

signals:
    void currentChanged();

protected:
    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);

    virtual void dragLeaveEvent(QDragLeaveEvent *e);
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dragMoveEvent(QDragMoveEvent *e);
    virtual void dropEvent(QDropEvent *e);



private:
    //virtual QDragData* dragObject();
    //void handleDrop(QDropEvent *e);
    void doCommonSetup();

private:
	bool typed, isLoaded;
	QString clName, typedMimeType;
    //RepositoryProperty *prop;
    //PObject *parentObject;
    QMenu *pmenu;
	Filter *filter;
    QWidget *prevWidget;
    PObjectListProvider *provider;
};


/*
class PObjectIconViewDrag : public QIconDrag
{
public:
    PObjectIconViewDragU(PObject *o, QWidget *source) : QIconDrag(source){
		this->o = o; className = o->getPersistenceObject()->getClassName(); typedMimeType=QString("application/pobject/").append(className);};
	
	
	static bool canDecode(QMimeSource* source);
	static  bool canDecode(QMimeSource* source, QString className);
	virtual QByteArray encodedData(const char* mimetype) const;
	virtual const char*  format(int i) const;
	//static PObjectIconViewItem* decode(QMimeSource* source, PObjectIconView *parent);
	static PObjectIconViewItem* decode(QMimeSource* source, PObjectIconView *parent);
	//void dragCopy();
	
private:
	PObject *o;
	QString className;
	QString typedMimeType;
};
*/



#endif
