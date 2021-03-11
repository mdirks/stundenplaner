#include "modehome.h"
#include "ui_modehome.h"

#include "gui/guirepository.h"

ModeHome::ModeHome() :
    GuiMode("Home"),
    ui(new Ui::ModeHome),
    displayWidget(0)
{

}

ModeHome::~ModeHome()
{
    delete ui;
}

void ModeHome::setupMode()
{
    GuiRepository *guirep=GuiRepository::getInstance();
    //guirep->setActiveMode(this);
    QStackedWidget *cw=guirep->getCentralWidget();

    if(!displayWidget){
        displayWidget=new QWidget(cw);
        ui->setupUi(displayWidget);
        cw->addWidget(displayWidget);


    }


    setModeWidget(displayWidget);
}


void ModeHome::tearDownMode()
{

}
void ModeHome::activateObject(PObject *o)
{
    GuiMode::activateObject(o);
}

void ModeHome::showForm(QWidget *w)
{
    GuiMode::showForm(w);
}

QList<QAction*>* ModeHome::getModeActions()
{
    return GuiMode::getModeActions();
}
