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
    } /*else if(mdata->hasUrls()){
        QList<QUrl> lurls=mdata->urls();
        if(lurls.size()>0 && lurls.at(0).isLocalFile()){
                QString file = lurls.at(0).toLocalFile();
                material *m  = materialmapper::getInstance()->create();
                m->setFileName(file.toStdString());
                QString name = KInputDialog::getText("Name fuer Material", "Materialname","Unbekannt");
                m->setName(name.toStdString());
                if(m){
                    qDebug("GenericMapView::contentsDropEvent : Adding to map from QUriDrag");
                    o=m;
                } else {
                    qDebug("Strange GenericMapView::contentsDropEvent : object was null");
                }
        }
        e->accept();
    }*/ else {
        qDebug("GenericMapView::contenstDropEvent : Decode of event failed");
    }


    if(o){
        if(lektuere *m = dynamic_cast<lektuere*>(o))
        {
            QString fileName = m->getFileName().c_str();
            if(fileName.contains(".pdf"))
            {
                loadNewFile(fileName);
                ModeLesen::getInstance()->setActiveText(m);
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

void PdfViewer::resizeEvent(QResizeEvent *event)
{
     QSize s=event->size();
     int widht= s.width();
     int pwidht = psize.width();

     //setZoomFactor(.81*widht/pwidht);
     if(resize){
         setZoomFactor(.75*widht/pwidht);
     }
}
