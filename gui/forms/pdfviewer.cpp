#include "pdfviewer.h"

#include "datamodel/lektuere.h"
#include "orm/persistence/database.h"
#include "gui/actions/modelesen.h"

#include <QDebug>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>

PdfViewer::PdfViewer(QWidget *parent)
    : PdfView(parent)
{
    slotToggleShowForms(true);


}


void PdfViewer::dragEnterEvent(QDragEnterEvent *e)
{
     qDebug() << "PdfViewer : DragEnter";
     //if(e->mimeData()->hasFormat("application/pobject")){
       e->acceptProposedAction();
    //}

}

void PdfViewer::dragMoveEvent(QDragMoveEvent* e)
{
    qDebug("PdfViewer : DragMove");
    /*
    if(PObjectDrag::canDecode(e)){

    }
    */
}
/*!
    \fn GenericMapView::contentsDropEvent(QDropEvent *e)
 */
 void PdfViewer::dropEvent(QDropEvent *e)
{
    qDebug("PdfViewer : Drop");

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
    } else {
        qDebug("GenericMapView::contenstDropEvent : Decode of event failed");
    }


    if(o){
        if(lektuere *m = dynamic_cast<lektuere*>(o))
        {
            QString fileName = m->getFileName().c_str();
            if(fileName.contains(".pdf"))
            {
                qDebug("WARNING: PdfViewer::dropEvent(QDropEvent *e) not finished - do nothing");
                //loadNewFile(fileName);
                //ModeLesen::getInstance()->setActiveText(m);
            }
        }
    }



}





void PdfViewer::loadNewFile(QString fileName)
{
     close();
     load(fileName);
     doInitialSetup();
}

void PdfViewer::loadNewData(const QByteArray &fileContents, QString name)
{
     close();
     load(fileContents,name);
     doInitialSetup();
}

void PdfViewer::doInitialSetup()
{
    Poppler::Document *doc=document();
    if(doc){
         int n = doc->numPages();
         Poppler::Page *page=doc->page(n/2);
         psize = page->pageSize();
     }
}


void PdfViewer::setResizePolicy(bool res)
{
    resize=res;
}

