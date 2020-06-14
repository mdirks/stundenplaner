#ifndef MTREEWIDGET_H
#define MTREEWIDGET_H

#include <QTreeWidget>
#include "orm/mapping/mtree.h"
#include "draganddrop/pobjectdroptarget.h"
#include <list>

using namespace std;

class MTreeWidgetItem;

class MTreeWidget : public QTreeWidget, public PObjectDropTarget
{
    Q_OBJECT

public:
    MTreeWidget(MTree *tr=0, QWidget *parent=0);
    void addTopLevelItem(MTree *tr);

public slots:
    void onCustomContextMenu(const QPoint &);

protected:
    //void mousePressEvent(QMouseEvent *e);
    //void keyPressEvent(QKeyEvent *e);

    //virtual void dragLeaveEvent(QDragLeaveEvent *e);
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dragMoveEvent(QDragMoveEvent *e);
    virtual void dropEvent(QDropEvent *e);



private:
    list<MTreeWidgetItem*> *topLevelItems;
};




class MTreeWidgetItem : public QTreeWidgetItem
{
public:
    MTreeWidgetItem(MTree *tr, QTreeWidgetItem *parentItem);
    MTreeWidgetItem(MTree *tr, QTreeWidget *parentWidget);

    void addChildItem(TransactionObject *to);
    void setContents(TransactionObject *to);
    TransactionObject* getContents();

private:
    MTree *node;
};


class MTreeWidgetItemAction : public QObject
{

Q_OBJECT

public:
    MTreeWidgetItemAction(MTreeWidgetItem *treeWidgetItem);
    ~MTreeWidgetItemAction();

public slots:
    void addChild();
    void removeFromParent();
    void newContentsObject();
};
#endif // MTREEWIDGET_H
