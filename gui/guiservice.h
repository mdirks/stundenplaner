#ifndef GUISERVICE_H
#define GUISERVICE_H

#include "guimode.h"
#include "gui/draganddrop/pobjectdroptarget.h"
#include <QAction>
#include <QToolButton>

class GuiService : public GuiMode/*public QAction*/
{
    Q_OBJECT
public:
    explicit GuiService(QString title);
    virtual void handleObject(PObject *)=0;

signals:
    
public slots:
    
};

class GuiServiceToolButton : public QToolButton, public PObjectDropTarget
{
    Q_OBJECT
public:
        GuiServiceToolButton(GuiService *s,QWidget *parent=0);
        void dropEvent(QDropEvent *event);
        void dragEnterEvent(QDragEnterEvent *e);
        void dragMoveEvent(QDragMoveEvent *e);
private:
    GuiService *serv;
};

/*
class ToolBar : public QToolBar
{
        public:
                ToolBar(QMainWindow *window) : QToolBar(window)
                {
                        setAcceptDrops(true);
                }

                void dragEnterEvent(QDragEnterEvent *event)
                {
                        if (event->mimeData()->hasFormat("bla/x-something"))
                                event->acceptProposedAction();
                }

                void dropEvent(QDropEvent *event)
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
};
*/

#endif // GUISERVICE_H
