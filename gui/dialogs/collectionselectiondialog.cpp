#include "collectionselectiondialog.h"

#include "gui/forms/pobjectlistprovider.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

CollectionSelectionDialog::CollectionSelectionDialog(PObject *po, RepositoryProperty *rp, QWidget *parent)
{
    listAll = new PObjectIconView(rp,po);

    listDisplay = new PObjectIconView(this);

    PoLListProvider *prov = new PoLListProvider(new list<PObject*>(), rp->getType().c_str());
    listDisplay->setObjectListProvider(prov);

    labelDisplay = new QLabel("Display");
    labelAll = new QLabel("Alle");

    QWidget *wDisplay = new QWidget(this);
    QVBoxLayout *lDisplay = new QVBoxLayout(wDisplay);
    lDisplay->addWidget(labelDisplay);
    lDisplay->addWidget(listDisplay);

    QWidget *wAll = new QWidget(this);
    QVBoxLayout *lAll = new QVBoxLayout(wAll);
    lAll->addWidget(labelAll);
    lAll->addWidget(listAll);

    QHBoxLayout *l = new QHBoxLayout(this);
    l->setSpacing(0);
    l->addWidget(wDisplay);
    l->addWidget(wAll);

}

CollectionSelectionDialog::~CollectionSelectionDialog()
{

}

list<PObject*>* CollectionSelectionDialog::getSelection()
{
    return listDisplay->getProvider()->objectList();
}

