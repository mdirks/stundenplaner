#ifndef COLLECTIONDISPLAY_H
#define COLLECTIONDISPLAY_H
#include "gui/forms/pobjecticonview.h"
#include <QWidget>

namespace Ui {
class CollectionDisplay;
}

class CollectionDisplay : public QWidget
{
    Q_OBJECT

public:
    CollectionDisplay(QWidget *parent=nullptr);
    explicit CollectionDisplay(QString clName, QString propName, QWidget *parent = nullptr);
    ~CollectionDisplay();

    PObject* getCurrentItem();
    void setContents(QString clName, QString propName);
    void addDropHandler_collection(PObjectIconViewDropHandler *dh);
    void addDropHandler_items(PObjectIconViewDropHandler *dh);

public slots:
    void changeCollection();
    void changeItem();

signals:
    void itemChanged();
    
private:
    Ui::CollectionDisplay *ui;

    PObjectListProvider *prov;
};

#endif // COLLECTIONDISPLAY_H
