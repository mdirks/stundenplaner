#include "pobjectmultiview.h"
#include "formspopupfactory.h"

PObjectMultiView::PObjectMultiView(RepositoryProperty *prop, PObject *parentObject,QWidget *parent) :
    QStackedWidget(parent)
{
    table = new PObjectTable(prop,parentObject,this);
    iconView = new PObjectIconView(prop,parentObject,this);


    addWidget(iconView);
    addWidget(table);
    setCurrentWidget(iconView);
}


void PObjectMultiView::load()
{
    table->load();
    iconView->load();
}

void PObjectMultiView::switchView()
{
    if(currentWidget()==table){
        setCurrentWidget(iconView);
    } else {
        setCurrentWidget(table);
    }
}

bool PObjectMultiView::isIconView()
{
    return currentWidget() == iconView;
}

PObjectTable* PObjectMultiView::getTable()
{
    return this->table;
}

PObjectIconView* PObjectMultiView::getIconView()
{
    return this->iconView;
}

QMenu* PObjectMultiView::getPopupMenu()
{

    FormsPopupFactory *factory = FormsPopupFactory::getInstance();
    if(factory){
        return factory->getPopupFor(this);
    } else {
        return 0;
    }

}

void PObjectMultiView::mousePressEvent(QMouseEvent *e)
{
     if(e->button()==Qt::RightButton){
        QMenu *popup = getPopupMenu();
        if(popup){
            popup->popup(e->globalPos());
        } else {
            qWarning("Failed to get Popupmenu");
        }
     } else {
         QStackedWidget::mousePressEvent(e);
     }


}
