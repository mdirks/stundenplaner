//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "genericmapview.h"

#include <qpoint.h>
#include <QGraphicsScene>
//#include <qwmatrix.h>
#include <qmessagebox.h>
#include <QMouseEvent>

#include <QFileDialog>
//#include <kaction.h>
#include <krun.h>

//#include "gui/draganddrop/pobjectdrag.h"
#include "services/actions/relateaction.h"
#include "services/actions/createaction.h"
#include "orm/transactions/transactions.h"
#include "gui/guirepository.h"
#include "gui/forms/pobjectdialog.h"
#include "gui/actions/datenpopup.h"
#include "mapviewspopupfactory.h"
#include "datamodel/stundenplaneintrag.h"
#include "datamodel/materialmapper.h"

#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"

#include "gui/forms/textpropertyviewer.h"
#include "gui/data/sitzplanmap.h"
#include "gui/data/sitzplanmapmapper.h"
#include "gui/data/pobjectgraphicsitemnp.h"
#include "gui/mapviews/sitzplanmapview.h"
#include "gui/actions/sitzplanmapviewcontroler.h"

#include "services/reports/latexoutput.h"

#include <qinputdialog.h>


GenericMapView::GenericMapView(QWidget * parent, const char * name) : QGraphicsView(parent)
{
	//popupMenu = new ThemaMapPopup();
	pmenu = 0;
	map=0;
	selectedItem = 0;
	
    setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);
    viewport()->setAcceptDrops(true);

	

}


GenericMapView::~GenericMapView()
{
}



void GenericMapView::resizeEvent ( QResizeEvent * event )
{
    if(scene()){
        fitInView(scene()->sceneRect(),Qt::KeepAspectRatio);
    }
    QGraphicsView::resizeEvent(event);

}

void GenericMapView::mousePressEvent( QMouseEvent* e )
{
     if(selectedItem){
		selectedItem->setSelected(false);
		selectedItem =0;
     }
     QPoint pos = e->pos();

    PObjectGraphicsItemNP *preselectItem =
            dynamic_cast<PObjectGraphicsItemNP*>(
                itemAt(pos));
    if(preselectItem){
        preselectItem->setSelected(true);
    } else {
        movingItem=0;
    }


     	
     
    if(e->button()==Qt::RightButton){
            selectedItem = preselectItem;
            currentPos =e->globalPos();
            emit(popupRequested(currentPos));
            movingItem=0;
    } else if (e->button() == Qt::LeftButton){
        movingItem = preselectItem;
        selectedItem=preselectItem;
        if(selectedItem){
            if(PObjectGraphicsItem *citem = dynamic_cast<PObjectGraphicsItem*>(movingItem)){
                Transactions::getCurrentTransaction()->add(citem);
            }
            GuiRepository::getInstance()->setSelectedObject(selectedItem->getObject());
    	}

     }
     getMap()->update();
}


void GenericMapView::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(selectedItem){
	selectedItem->setSelected(false);
    }

     QPoint pos = e->pos();
     QList<QGraphicsItem*>  itemList=items(pos);
     QGraphicsItem *preselectItem =0;
     if(! itemList.empty()){
     	selectedItem = dynamic_cast<PObjectGraphicsItemNP*>(*(itemList.begin()));
	if(selectedItem){
		selectedItem->setSelected(true);
		emit activateSelectedRequested(selectedItem);
		//activateSelected();
	}
    }
}

void GenericMapView::wheelEvent ( QWheelEvent * event )
{
    /*
    double factor = 1.41*(-event->delta() /240.0);
    scale(factor,factor);
    */
}

void GenericMapView::mouseMoveEvent ( QMouseEvent * e )
{
 	if(movingItem){

        //QPointF p = mapFromGlobal(e->globalPos());
        QPointF p = mapToScene(e->pos());
        movingItem->setX(p.x());
        movingItem->setY(p.y());
        //movingItem->moveBy(p.x()-movingItem->x(),p.y()-movingItem->y());
        /*
        movingItem->moveBy(e->pos().x()-movingItem->x(),e->pos().y()-movingItem->y());
		getMap()->update();
        */
	}
}

/*!
    \fn GenericMapView::getGenericMap()
 */
GenericMap* GenericMapView::getMap()
{
    return map;
}


/*!
    \fn GenericMapView::setGenericMap(GenericMap *map)
 */
void GenericMapView::setMap(GenericMap *map)
{
    this->map = map;
    //popupMenu->setMap(map);
    
    QGraphicsView::setScene(map);
    map->displayMap();
}


/*!
    \fn GenericMapView::keyPressEvent(QKeyEvent *e)
 */
void GenericMapView::keyPressEvent(QKeyEvent *e)
{
    qDebug("GenericMapView : Key Pressed");
}





/*!
    \fn GenericMapView::contentsDragEnterEvent(QDragEnterEvent *e)
 */
void GenericMapView::dragEnterEvent(QDragEnterEvent *e)
{
     qDebug() << "GenericMapView : DragEnter";
     //if(e->mimeData()->hasFormat("application/pobject")){
       e->acceptProposedAction();
    //}
	
}

void GenericMapView::dragMoveEvent(QDragMoveEvent* e)
{
	qDebug("GenericMapView : DragMove");
	/*
	if(PObjectDrag::canDecode(e)){
		
	}
	*/
}
/*!
    \fn GenericMapView::contentsDropEvent(QDropEvent *e)
 */
 void GenericMapView::dropEvent(QDropEvent *e)
{
     qDebug("GenericMapView : Drop");

    QPoint eventPos = e->pos();
    QPointF graphicsPos = mapToScene(eventPos);
	PObject *o=0;
    const QMimeData *mdata = e->mimeData();
    if(mdata->hasFormat("application/pobject") ){ // recieved a valid object
        QByteArray data=e->mimeData()->data("application/pobject");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QString className;
        int id;
        stream >> className >> id;
        o = Database::getInstance()->load(className.toStdString(), id);
        /*
             o= PObjectData::decode(e->mimeData()->data("application/pobject"));
         */
        if(o){
            e->accept();
        }else{
            e->ignore();
            qDebug() << "GenericMapView::contentsDropEvent: Strange, how to decode this data?";
        }
    } else if(mdata->hasUrls()){
        QList<QUrl> lurls=mdata->urls();
        if(lurls.size()>0 && lurls.at(0).isLocalFile()){
                QString file = lurls.at(0).toLocalFile();
                material *m  = materialmapper::getInstance()->create();
                m->setFileName(file.toStdString());
                QString name = QInputDialog::getText(this,"Name fuer Material", "Materialname",QLineEdit::Normal,"Unbekannt");
                m->setName(name.toStdString());
                if(m){
                    qDebug("GenericMapView::contentsDropEvent : Adding to map from QUriDrag");
                    o=m;
                } else {
                    qDebug("Strange GenericMapView::contentsDropEvent : object was null");
                }
		}
		e->accept();
    } else {
        qDebug("GenericMapView::contenstDropEvent : Decode of event failed");
    }
	

	if(o){
        QList<QGraphicsItem*> col  = items(eventPos); //getMap()->items(eventPos);
		if(! col.isEmpty() ){
			bool done = false;
            QList<QGraphicsItem*>::iterator it;
			for(it = col.begin(); it != col.end(); it++){
				if(PObjectGraphicsItemNP *oci = dynamic_cast<PObjectGraphicsItemNP*>( (*it) ))
				{
					bool done_here = RelateAction::getInstance()->relate(o,oci->getObject());
					if(done_here){
						qDebug("Adding via relation");
						Transactions::getCurrentTransaction()->add(o);
						Transactions::getCurrentTransaction()->add(oci->getObject());
						oci->update();
					} 
					done = (done | done_here);
				}
				
			}
			if(!done){
				qDebug("Adding to map without relation");
                map->addItem(o,graphicsPos);
			}
		}  else {
			qDebug("Collisionlist was empty");
            map->addItem(o,graphicsPos);
		}
		//qDebug("GenericMapView::contentsDropEvent : Adding to map from PObjectDrag");
		//map->addItem(o,GraphicsPos);
		map->save();
	   } else {
		qWarning("GenericMapView::contenstDropEvent : decoded Object invalid");
	   }
      
      
      
}




/*!  Deletes the selected item from the map

	

    \fn GenericMapView::deleteSelected()
 */
/*
void GenericMapView::deleteSelected()
{
    if(PObjectGraphicsItemNP *pitemnp = dynamic_cast<PObjectGraphicsItemNP*>(selectedItem)){
	pitemnp->setVisible(FALSE);
	selectedItem=0;
	if(PObjectGraphicsItem *pitem = dynamic_cast<PObjectGraphicsItem*>(pitemnp)){
		Transactions::getCurrentTransaction()->add(getMap());
		getMap()->deleteFromGraphicsItems(pitem);
	}	
	getMap()->update();
	/** \todo How to properly delete an item ? */
	//delete pitem;
	/*
    }
}
*/
/*!
    \fn GenericMapView::itemDown()
 */
/*
void GenericMapView::itemDown()
{
	if(PObjectGraphicsItemNP* npitem = dynamic_cast<PObjectGraphicsItemNP*>(selectedItem)){
    		npitem->setZ(npitem->z() -2);
		if(PObjectGraphicsItem *pitem = dynamic_cast<PObjectGraphicsItem*>(npitem)){
			Transactions::getCurrentTransaction()->add(pitem);
		}
	}
	getMap()->update();
}


/*!
    \fn GenericMapView::itemUp()
 */
/*
void GenericMapView::itemUp()
{
    if(PObjectGraphicsItemNP* npitem = dynamic_cast<PObjectGraphicsItemNP*>(selectedItem)){
    		npitem->setZ(npitem->z() +2);
		if(PObjectGraphicsItem *pitem = dynamic_cast<PObjectGraphicsItem*>(npitem)){
			Transactions::getCurrentTransaction()->add(pitem);
		}
	}
	getMap()->update();
}
*/
/*!
    \fn GenericMapView::activateSelected()
 */

void GenericMapView::activateSelected()
{
    	qDebug("GenericMapView::activateSelected : do nothing implementation called");
}




/*!
    \fn GenericMapView::getPopupMenu()
 */
QMenu* GenericMapView::getPopupMenu()
{
  	MapviewsPopupFactory *factory = MapviewsPopupFactory::getInstance();
	if(factory){
		return factory->getPopupForGenericMapView(this,currentPos);
	} else {
        return new QMenu();
	}


}






ShowSitzplanAction::ShowSitzplanAction(stundenplaneintrag *se, QObject *parent)
    : QAction("Sitzplan", parent)
{
	this->se = se;
    connect(this, SIGNAL(triggered(bool)) , this, SLOT( showSitzplan() ) );
}

ShowSitzplanAction::~ShowSitzplanAction(){}

void ShowSitzplanAction::showSitzplan()
{
	if(se){
		if(klasse *kl = se->getKlasse()){
            sitzplan *sp = kl->getSitzplan();
			if(sp){
                GuiRepository::getInstance()->showFormForObject(sp,false);

			} else {
				qDebug("ShowSitzplanAction::showSitzplan : no sitzplan in klasse");
			}
		} else {
			qDebug("ShowSitzplanAction::showSitzplan : Could not get Klasse from Stundenplaneintrag");
		}
	} else {
		qDebug("ShowSitzplanAction::showSitzplan : Stundenplaneintrag not set");
	}
}


SitzplanMap*  ShowSitzplanAction::getMapForSitzplan(sitzplan *sp)
{
    	list<PObject*> *list_maps = SitzplanMapmapper::getInstance()->find_gen();
	SitzplanMap *result=0;
	list<PObject*>::iterator it = list_maps->begin();
	while(it != list_maps->end() && result ==0)
	{
		SitzplanMap *sm = dynamic_cast<SitzplanMap*>(*it);
		if(sm){
			if(sm->getSitzplan() == sp) result = sm;
		}
		it++;
	}
	if(!result){
		result = (SitzplanMap*) SitzplanMapmapper::getInstance()->create();
		result->setSitzplan(sp);
		result->loadSitzplan();
	}
	return result;
}


/*!
    \fn GenericMapView::getSelected()
 */
PObjectGraphicsItemNP* GenericMapView::getSelected()
{
    return selectedItem;
}

void GenericMapView::clearSelection()
{
    selectedItem = 0;
}


/*!
    \fn GenericMapView::getSelectedObject()
 */
PObject* GenericMapView::getSelectedObject()
{
    	PObject *o=0;
    	PObjectGraphicsItemNP* ci = getSelected();
	if(ci){
		o = ci->getObject();
	}
	return o;
}
