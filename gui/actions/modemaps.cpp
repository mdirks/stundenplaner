#include "modemaps.h"
#include "ui_modemaps.h"

#include "gui/guirepository.h"
#include "gui/actions/genericmapviewcontroler.h"
#include <QStackedWidget>

ModeMaps::ModeMaps()
    : GuiMode("Maps"),
      ui(new Ui::ModeMapsCentral),
      m_map(0)

{
    displayWidget=0;
}

ModeMaps::~ModeMaps()
{
    delete ui;
}

void ModeMaps::setupMode()
{
    GuiRepository *guirep=GuiRepository::getInstance();
    //guirep->setActiveMode(this);
    QStackedWidget *cw=guirep->getCentralWidget();

    if(!displayWidget){
        displayWidget=new QWidget(cw);
        ui->setupUi(displayWidget);
        //displayWidget->show();
        cw->addWidget(displayWidget);
        ui->collDisp->setContents("ThemaMapSatz","ThemaMaps");

        connect(ui->collDisp,SIGNAL(itemChanged()),this,SLOT(activateNewMap()));

        new GenericMapViewControler(ui->mapView);
        loadContentsList();
    }


    setModeWidget(displayWidget);
}

void ModeMaps::loadContentsList()
{
    if(m_map){
        if(thema* t=m_map->getThema()){
            list<PObject*> *ol = new list<PObject*>();
            list<notiz*> *nl=t->getNotizen();
            ol->insert(ol->end(), nl->begin(), nl->end());
            list<material*> *ml=t->getMaterialien();
            ol->insert(ol->end(), ml->begin(), ml->end());
            ui->contentsList->setObjectListProvider(new PoLListProvider(ol));


        }
    }


}

void ModeMaps::tearDownMode()
{
    //if(toolBar) toolBar->hide();
}
void ModeMaps::activateObject(PObject *o)
{
    qDebug() << QString("TODO: ModeMaps::activateObject");
}

void ModeMaps::showForm(QWidget *w)
{
    qDebug() << QString("TODO: ModeMaps::activateObject");
}

QList<QAction*>* ModeMaps::getModeActions()
{
    qDebug() << QString("TODO: ModeMaps::activateObject");
}


void ModeMaps::activateNewMap()
{
    PObject *o=ui->collDisp->getCurrentItem();
    if(ThemaMap* tm=dynamic_cast<ThemaMap*>(o)){
        m_map=tm;
        ui->mapView->setMap(tm);
        loadContentsList();
    }
}
