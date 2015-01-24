#include "modelernen.h"
#include "gui/base/guiconfig.h"
#include "gui/guirepository.h"
#include "gui/forms/pobjectdisplay.h"
#include "orm/mapping/mappingcontroler.h"
#include "gui/forms/pobjectlistprovider.h"

#include <QStackedWidget>
#include <QHBoxLayout>

ModeLernen::ModeLernen()
    : GuiMode("Lernen")
{
    QPixmap pm = GuiConfig::getInstance()->getIcon("ModeLernen");

    /*
    if(pm.isNull()){
        GuiConfig::getInstance()->selectIcon("ModeLernen");
        pm = GuiConfig::getInstance()->getIcon("ModeLesen");
    }
    */
    setIcon(pm);




    mainWidget=0;
    toolBar=0;


}

void ModeLernen::setupMode()
{

    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();

    guirep->setActiveMode(this);
    if(!mainWidget){
        mainWidget = new QWidget(sw);

        PObjectListProvider *prov=new MapperListProvider("lernkartensatz");
        combo=new PObjectComboBox(prov,mainWidget);

        objectDisplay = new PObjectDisplay(mainWidget);
        objectDisplay->setPrototype(new LernkarteDisplayItem());
        editor = new PObjectIconView(mainWidget);
        editor->setMinimumWidth(400);
        editor->hide();

        QVBoxLayout *l = new QVBoxLayout();
        l->addWidget(combo);
        l->addWidget(objectDisplay);
        QHBoxLayout *vl = new QHBoxLayout();
        vl->addLayout(l);
        vl->addWidget(editor);
        mainWidget->setLayout(vl);
        sw->addWidget(mainWidget);

        connect(combo,SIGNAL(activated(int)),this,SLOT(newListSelected(int)));
    }
    sw->setCurrentWidget(mainWidget);


    if(!toolBar){
        toolBar = new QToolBar(guirep->getMainFrame());
        QPixmap pm = GuiConfig::getInstance()->getIcon("Karteneditor");
        toolBar->addAction(pm,"",this,SLOT(showKartenEditor()));
        guirep->getMainFrame()->addToolBar(Qt::RightToolBarArea,toolBar);
    } else {
        toolBar->show();
    }
}

void ModeLernen::tearDownMode()
{

}

void ModeLernen::activateObject(PObject *o)
{


}

void ModeLernen::showForm(QWidget *w)
{

}

QList<QAction*>* ModeLernen::getModeActions()
{

}

void ModeLernen::newListSelected(int i)
{
    PObject *o=combo->getObject(i);
    if(lernkartensatz *lks = dynamic_cast<lernkartensatz*>(o)){
        objectDisplay->setObjectList((list<PObject*>*) lks->getLernkarten());
        editor->setObjectListProvider(new PoLListProvider( (list<PObject*>*) lks->getLernkarten(), "lernkarte" ));
    }
}

void ModeLernen::showKartenEditor()
{
    if(editor->isVisible()){
        editor->hide();
    } else {
        editor->show();
    }
}
