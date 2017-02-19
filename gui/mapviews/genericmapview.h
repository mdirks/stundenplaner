//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GENERICMAPVIEW_H
#define GENERICMAPVIEW_H


#include <QGraphicsView>
#include <QMenu>
#include <QAction>
//#include <kaccel.h>
//#include <qaction.h>

#include "gui/data/genericmap.h"
#include "themamappopup.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/persistence/pobject.h"
#include "datamodel/stundenplaneintrag.h"
#include "gui/data/sitzplanmap.h"


/**
@author Marcus Dirks
*/
class GenericMapView : public QGraphicsView
{
Q_OBJECT

public:
    GenericMapView(QWidget * parent = 0, const char * name = 0);

    ~GenericMapView();
    
    void setMap(GenericMap *map);
    GenericMap* getMap();
    
    //virtual list<QAction*>* initActions(QActionCollection *parent=0);
    //virtual list<QAction*>* initActionsForSelection(QActionCollection *parent=0);
    virtual QMenu* getPopupMenu();
    PObjectGraphicsItemNP* getSelected();
    void clearSelection();
    PObject* getSelectedObject();
    

public slots:
    void activateSelected();
    //void showFormForSelected();
    //void deleteSelected();
    //void zoomIn();
    //void zoomOut();
    //void writeLatex();
    //void createNewItem();
    //void itemDown();
    //void itemUp();

signals:
	void popupRequested(QPoint pos);
	void activateSelectedRequested(PObjectGraphicsItemNP *selectedItem);

protected:
    QMenu *pmenu;
    virtual void resizeEvent ( QResizeEvent * event );


private:
     GenericMap *map;
     //ThemaMapPopup *popupMenu;
     PObjectGraphicsItemNP *movingItem, *selectedItem;

protected:     
     QPoint currentPos;
     
protected:
    virtual void mousePressEvent( QMouseEvent* e );
    virtual void mouseMoveEvent ( QMouseEvent * e );

    virtual void keyPressEvent(QKeyEvent *e);
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dropEvent(QDropEvent *e);
    virtual void dragMoveEvent(QDragMoveEvent* e);

    //QPopupMenu *getDatenPopupForSelected();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void wheelEvent ( QWheelEvent * event );

};




class ShowSitzplanAction : public QAction 
{
Q_OBJECT

public:
	ShowSitzplanAction(stundenplaneintrag *se, QObject *parent);
	~ShowSitzplanAction();

public slots:
	void showSitzplan();

protected:
	SitzplanMap*  getMapForSitzplan(sitzplan *sp);

private:
	stundenplaneintrag *se;
};









#endif
