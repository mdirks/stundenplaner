#ifndef ELEMENTMODEL_H
#define ELEMENTMODEL_H


#include <QAbstractListModel>
#include <QDomDocument>
#include <QModelIndex>

//class DomItem;

class ElementModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ElementModel(const QDomElement &element, QObject *parent = nullptr);
    ~ElementModel();

    QVariant data(const QModelIndex &index, int role) const override;
    //Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    //QModelIndex index(int row, int column,
    //                  const QModelIndex &parent = QModelIndex()) const override;
    //QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    //QDomElement element(const QModelIndex &index);
private:
    QDomElement domElement;
    QDomNamedNodeMap nodeMap;
    //DomItem *rootItem;
};


#endif // ELEMENTMODEL_H
