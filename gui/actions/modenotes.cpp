#include "modenotes.h"

#include "gui/guirepository.h"
#include "gui/base/guiconfig.h"
#include "gui/forms/pobjectlistprovider.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include <QHBoxLayout>
#include <QPixmap>

ModeNotes::ModeNotes()
    : GuiMode("Notizen")
{
    viewSaetze=0;
    viewNotizen=0;
    sviewSaetze=0;
    sviewNotizen=0;

    prov=0;
    sprov=0;

    splitter=0;
    displayWidget=0;
    sdisplayWidget=0;
    editorWidget=0;
    toolBar=0;

    QPixmap pm = GuiConfig::getInstance()->getIcon("ModeNote");

    /*
    if(pm.isNull()){
        GuiConfig::getInstance()->selectIcon("ModeNotes");
        pm = GuiConfig::getInstance()->getIcon("ModeNotes");
    }
    */


    setIcon(pm);

}


void ModeNotes::setupMode()
{
    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();

    if(!splitter){
        splitter = new QSplitter(Qt::Horizontal,sw);
        displayWidget = new QWidget(splitter);

        viewSaetze= new PObjectIconView("notizsatz",displayWidget);
        viewNotizen = new PObjectIconView(displayWidget);


        QHBoxLayout *hl = new QHBoxLayout(displayWidget);
        hl->setContentsMargins(0,0,0,0);
        hl->setSpacing(0);
        //hl->setMargin(0);

        /*
        viewNotizen->setFrameStyle(QFrame::Panel | QFrame::Plain);
        viewNotizen->setLineWidth(1);
        QPalette p = viewNotizen->palette();
        p.setColor(QPalette::WindowText, Qt::red);
        viewNotizen->setPalette(p);
        */

        viewNotizen->setFrameShape(QFrame::StyledPanel);
        //viewNotizen->setStyleSheet( "border-width: 2px; border-top-style: none; border-right-style: solid; border-bottom-style: solid; border-left-style: none; border-color: blue; ");
        viewNotizen->setStyleSheet( "border-width: 1px; border-top-style: none; border-right-style: none; border-bottom-style: none; border-left-style: solid;");

        //viewNotizen->setFrameStyle(QFrame::NoFrame);
        //viewNotizen->setMidLineWidth(3);

        //viewNotizen->setContentsMargins(0,0,0,0);
        //viewNotizen->setSpacing(0);


        viewSaetze->setFrameShape(QFrame::StyledPanel);
        viewSaetze->setStyleSheet( "border-width: 0px; border-top-style: none; border-right-style: solid; border-bottom-style: none; border-left-style: none; border-color: black; ");
        //viewSaetze->setSpacing(0);
        //viewSaetze->setStyleSheet("margin: 0; padding: 0;");
        hl->addWidget(viewSaetze,15);
        hl->addWidget(viewNotizen,25);

        splitter->setContentsMargins(1,1,1,1);
        splitter->addWidget(displayWidget);
        //splitter->setStyleSheet("margin: 0; padding: 0;");
        RepositoryProperty *rp = Repository::getInstance()->getRepositoryEntry("notiz")->getProperty("Body");

        /*
        viewer = new TextPropertyViewer(0,rp,displayWidget);
        */
        viewer = new TextPropertyViewer2(0,rp,displayWidget);
        editorWidget=new QStackedWidget(displayWidget);
        editorWidget->setFrameStyle(QFrame::NoFrame);
        editorWidget->setContentsMargins(0,0,0,0);
        editorWidget->addWidget(viewer);
        editorWidget->setCurrentWidget(viewer);

        splitter->addWidget(editorWidget);



        sw->addWidget(splitter);

        rp= Repository::getInstance()->getRepositoryEntry("notizsatz")->getProperty("Notizen");
        prov = new RpListProvider(rp);
        sprov = new RpListProvider(rp);

        connect(viewSaetze,SIGNAL(currentChanged()),this,SLOT(changeSatz()));
        connect(viewNotizen,SIGNAL(currentChanged()),this,SLOT(changeNotiz()));
    }
    sw->setCurrentWidget(splitter);

    if(!toolBar){
        toolBar = new QToolBar(guirep->getMainFrame());
        QPixmap pm = GuiConfig::getInstance()->getIcon("NotizSelector");
        toolBar->addAction(pm," ",this,SLOT(showSelector()));

        /*
        pm = GuiConfig::getInstance()->getIcon("Lernkarten");
        toolBar->addAction(pm,"",this,SLOT(showLernkarten()));
        */

        guirep->getMainFrame()->addToolBar(Qt::RightToolBarArea,toolBar);
    } else {
        toolBar->show();
    }
}

void ModeNotes::tearDownMode()
{
    toolBar->hide();
}

void ModeNotes::changeSatz()
{
    if(prov){
        PObject *o=viewSaetze->getCurrent();
        if(o){
            prov->setParentObject(o);
            viewNotizen->setObjectListProvider(prov);
            viewNotizen->setCurrentRow(0);
        }
    }
}

void ModeNotes::changeSelectorSatz()
{
    if(sprov){
        PObject *o=sviewSaetze->getCurrent();
        if(o){
            sprov->setParentObject(o);
            sviewNotizen->setObjectListProvider(sprov);
            sviewNotizen->setCurrentRow(0);
        }
    }
}

void ModeNotes::changeNotiz()
{
    PObject *o=viewNotizen->getCurrent();
    if(o){
        viewer->setParentObject(o);
    }
}

void ModeNotes::showSelector()
{
    if(!sdisplayWidget){
        sdisplayWidget = new QWidget();
        QHBoxLayout *hl= new QHBoxLayout(sdisplayWidget);

        sviewSaetze= new PObjectIconView("notizsatz",displayWidget);
        sviewNotizen = new PObjectIconView(displayWidget);

        hl->addWidget(sviewNotizen,15);
        hl->addWidget(sviewSaetze,15);

        editorWidget->addWidget(sdisplayWidget);
        connect(sviewSaetze,SIGNAL(currentChanged()),this,SLOT(changeSelectorSatz()));
    }
    if(editorWidget->currentWidget()!=sdisplayWidget){
        editorWidget->setCurrentWidget(sdisplayWidget);
    } else {
        editorWidget->setCurrentWidget(viewer);
    }




}
