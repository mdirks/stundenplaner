#include "guimode.h"

#include "guirepository.h"

GuiMode::GuiMode(QString title)
    : QAction(title,0)
{
    connect(this,SIGNAL(triggered()),this,SLOT(doSetupMode()));
    modeWidget=0;
    emptyWidget=new QWidget();
    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();
    sw->addWidget(emptyWidget);

    modeToolBar = new QToolBar(guirep->getMainFrame());
    guirep->getMainFrame()->addToolBar(Qt::RightToolBarArea,modeToolBar);
    setupDone=false;
}

void GuiMode::doSetupMode()
{
    qWarning() << "GuiMode::doSetupMode " << text();
    GuiRepository::getInstance()->setActiveMode(this);
}

void GuiMode::reload()
{
    close();
    load();
}

void GuiMode::setModeWidget(QWidget *w)
{
    modeWidget=w;
    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();
    sw->addWidget(modeWidget);
}

void GuiMode::close()
{
    if(modeWidget){
        GuiRepository *guirep=GuiRepository::getInstance();
        QStackedWidget *sw=guirep->getCentralWidget();
        sw->removeWidget(modeWidget);
        setupDone=false;
    }
}

void GuiMode::activate()
{
    if(!setupDone){
        setupMode();
        setupDone=true;
    }
    if(modeWidget){
        GuiRepository *guirep=GuiRepository::getInstance();
        QStackedWidget *sw=guirep->getCentralWidget();
        sw->setCurrentWidget(modeWidget);
    }
    modeToolBar->show();
}

void GuiMode::deactivate()
{
        GuiRepository *guirep=GuiRepository::getInstance();
        QStackedWidget *sw=guirep->getCentralWidget();
        sw->setCurrentWidget(emptyWidget);
        modeToolBar->hide();

}
