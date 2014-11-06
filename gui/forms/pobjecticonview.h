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
#include "orm/mapping/abstractmapper.h"
#include "gui/draganddrop/pobjectdata.h"
#include "pobjecticonviewitem.h"
#include "gui/base/propertyeditor.h"
#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryproperty.h"
#include "services/filter/filter.h"
#include "pobjecttable.h"


//#include <kiconview.h>
#include <kxmlguiclient.h>
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
class PObjectIconView : public QListWidget, public KXMLGUIClient, public PropertyEditor
{
Q_OBJECT

public:
	PObjectIconView(QWidget *parent=0);
	PObjectIconView(list<PObject*> *olist, QWidget *parent=0);
	PObjectIconView(AbstractMapper *mapper, QWidget *parent=0);
    	PObjectIconView(RepositoryProperty *prop, PObject *parentObject, QWidget *parent=0);

    	~PObjectIconView();
    	void load();
   	void load(list<PObject*>* olist);
   	void addObject(PObject *o);
	void deleteObject(PObjectIconViewItem *item);

	void stopEdit();
    	void startEdit(RepositoryProperty *rp, PObject *parent);
    	void startEdit();
    	//list<KAction*>* initActions(KActionCollection *parent=0);
    QMenu* getPopupMenu();
    list<PObject*>* getObjectList();
    AbstractMapper* getMapper();
    RepositoryProperty* getProperty();
    PObject* getParentObject();
    void setMapper(AbstractMapper *mapper);
	PObject* getSelected();
    virtual void 	startDrag ( Qt::DropActions supportedActions );
    void setTableView(PObjectTable *table);
    PObjectTable* getTableView();

protected:
	//QPopupMenu*  getDatenPopupForSelected();
private:
	AbstractMapper *mapper;
	QPixmap icon;
	bool editing;
	list<PObject*> *olist;
    PObjectTable *tableView;

public slots:
    void activateItem(QListWidgetItem *item);
    void reload();
    //void newIconView();
    //void configureView();
    void renameObject(QListWidgetItem* item);
    PObjectIconViewItem* createItem(PObject* o);
    //void selectIcon();
    void selectFile();

    void show();
    void chooseFilter();

protected:
    void mousePressEvent(QMouseEvent *e);

    virtual void dragLeaveEvent(QDragLeaveEvent *e);
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dragMoveEvent(QDragMoveEvent *e);
    virtual void dropEvent(QDropEvent *e);



private:
    //virtual QDragData* dragObject();
    void handleDrop(QDropEvent *e);

private:
	bool typed, isLoaded;
	QString clName, typedMimeType;
	RepositoryProperty *prop;
	PObject *parentObject;
    QMenu *pmenu;
	Filter *filter;
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
