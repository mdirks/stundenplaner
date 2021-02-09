#include "modemaps.h"
#include "ui_modemaps.h"

#include "gui/guirepository.h"
#include "gui/actions/genericmapviewcontroler.h"
#include <QStackedWidget>

ModeMaps::ModeMaps()
    : GuiMode("Maps"),
      ui(new Ui::ModeMapsCentral)

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
    }


    setModeWidget(displayWidget);
}

void ModeMaps::tearDownMode()
{
    //if(toolBar) toolBar->hide();
}
void ModeMaps::activateObject(PObject *o)
{

}

void ModeMaps::showForm(QWidget *w)
{

}

QList<QAction*>* ModeMaps::getModeActions()
{

}


void ModeMaps::activateNewMap()
{
    PObject *o=ui->collDisp->getCurrentItem();
    if(ThemaMap* tm=dynamic_cast<ThemaMap*>(o)){
        ui->mapView->setMap(tm);
    }
}
