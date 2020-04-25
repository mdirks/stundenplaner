#include "elementmodel.h"
//#include "domitem.h"

#include <QtXml>


ElementModel::ElementModel(const QDomElement &element, QObject *parent)
    : QAbstractTableModel(parent),
      domElement(element),
      nodeMap(element.attributes())
      //rootItem(new DomItem(domDocument, 0))
{
}

ElementModel::~ElementModel()
{
    //delete rootItem;
}

int ElementModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

int ElementModel::rowCount(const QModelIndex &parent) const
{
   return nodeMap.count();
}


QVariant ElementModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    //const DomItem *item = static_cast<DomItem*>(index.internalPointer());

    //const QDomNode node = item->node();

    QDomNode node=nodeMap.item(index.row());

    switch (index.column()) {
        case 0:
        {
           return node.nodeName();
        }



        case 1:
        {
            return node.nodeValue();
        }

       default:
            break;
    }
    return QVariant();
}

/*
Qt::ItemFlags ElementModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}
*/


QVariant ElementModel::headerData(int section, Qt::Orientation orientation,
                              int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0:
                return tr("Attribute");
            case 1:
                return tr("Value");
            default:
                break;
        }
    }
    return QVariant();
}

/*
QModelIndex ElementModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    DomItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<DomItem*>(parent.internalPointer());

    DomItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}
*/

/*
QModelIndex ElementModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
    DomItem *parentItem = childItem->parent();

    if (!parentItem || parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
*/




