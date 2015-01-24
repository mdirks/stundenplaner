#include "guiservice.h"

GuiService::GuiService(QString title) :
    GuiMode(title)/*QAction(parent)*/
{
}



GuiServiceToolButton::GuiServiceToolButton(GuiService *s, QWidget *parent) : QToolButton(parent)
{
    serv = s;

    setAcceptDrops(true);
    if(s){
        connect(this, SIGNAL(pressed()), s, SLOT(doSetupMode()));
    }
}

void GuiServiceToolButton::dropEvent(QDropEvent *event)
{
    PObject *o=handlePObjectDrop(event);
    if(o && serv){
        serv->handleObject(o);
    }
}


void GuiServiceToolButton::dragEnterEvent(QDragEnterEvent *e)
{

    if(e->mimeData()->hasFormat("application/pobject"))
    {
        e->accept();
    } else {
        e->ignore();
    }

}

void GuiServiceToolButton::dragMoveEvent(QDragMoveEvent *e)
{

    if(e->mimeData()->hasFormat("application/pobject"))
    {
        e->accept();
    } else {
        e->ignore();
    }

}



/*
GuiServiceToolBar::GuiServiceToolBar(QMainWindow *window) : QToolBar(window)
{
    setAcceptDrops(true);
}

void GuiServiceToolBar::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("bla/x-something")){
           event->acceptProposedAction();
    }
}

void GuiServiceToolBar::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("bla/x-something")) {
        event->accept();
        event->setDropAction(Qt::MoveAction);
        QByteArray pieceData = event->mimeData()->data("bla/x-something");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        ToolButton *button = new ToolButton(this);
        button->setText(pieceData);
        addWidget(button);
    } else {
        event->ignore();
    }
}
*/
