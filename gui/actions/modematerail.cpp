#include "modematerail.h"
#include "gui/guirepository.h"
#include "gui/base/guiconfig.h"
#include "gui/actions/guicreateaction.h"

#include <QStackedWidget>
#include <QSplitter>
#include <QTextStream>
#include <QVBoxLayout>

ModeMaterial* ModeMaterial::instance=0;

ModeMaterial::ModeMaterial()
    : GuiMode("Material")
{
    QPixmap pm = GuiConfig::getInstance()->getIcon("ModeMaterial");
    /*
    if(pm.isNull()){
        GuiConfig::getInstance()->selectIcon("ModePlanung");
        pm = GuiConfig::getInstance()->getIcon("ModePlanung");
    }
    */
    setIcon(pm);

    editor = new QTextEdit();
    viewer = new PdfViewer();
    toolBar=0;
    activeMaterial=0;
    //splitter=0;
    mainPanel=0;


}
ModeMaterial* ModeMaterial::getInstance()
{
    if(instance==0)
    {
        instance=new ModeMaterial();
    }
    return instance;
}

void ModeMaterial::setupMode()
{

    GuiRepository *guirep=GuiRepository::getInstance();
    guirep->setActiveMode(this);
    QStackedWidget *sw=guirep->getCentralWidget();
    if(!mainPanel){
        mainPanel = new QWidget(sw);
        sw->addWidget(mainPanel);
    } else {
        sw->setCurrentWidget(mainPanel);
    }

    if(!toolBar){
        toolBar = new QToolBar(guirep->getMainFrame());
        QPixmap pm = GuiConfig::getInstance()->getIcon("action_material_new");
        toolBar->addAction(pm,"",this,SLOT(createNew()));
        pm = GuiConfig::getInstance()->getIcon("action_material_open");
        toolBar->addAction(pm,"",this,SLOT(open()));
        pm = GuiConfig::getInstance()->getIcon("action_material_save");
        toolBar->addAction(pm,"",this,SLOT(save()));

        guirep->getMainFrame()->addToolBar(Qt::RightToolBarArea,toolBar);
    } else {
        toolBar->show();
    }
}

void ModeMaterial::setupLatex()
{
    GuiRepository *guirep=GuiRepository::getInstance();

    QSplitter *splitter = new QSplitter(Qt::Horizontal,mainPanel);
    splitter->addWidget(editor);
    splitter->addWidget(viewer);

    QVBoxLayout *l=new QVBoxLayout(mainPanel);
    l->addWidget(splitter);

    //sw->setCurrentWidget(splitter);

    if(activeMaterial){
        QFile *f = activeMaterial->getFile();
        f->open(QIODevice::ReadOnly);
        QTextStream in(f);
        editor->setText(in.readAll());
        f->close();
    }
}

void ModeMaterial::tearDownMode()
{
    if(toolBar) toolBar->hide();
}

void ModeMaterial::open()
{

}

void ModeMaterial::save()
{
    if(activeMaterial){
        QFile *f=activeMaterial->getFile();
        f->open(QIODevice::WriteOnly);
        QTextStream out(f);
        out << editor->toPlainText() << endl;
        f->close();
    }

}

void ModeMaterial::createNew()
{
    PObject *o =  GuiCreateAction::getInstance()->create("material");
    activeMaterial = dynamic_cast<material*>(o);
    if(activeMaterial){
        activeMaterial->getFile()->fileName().contains(".tex");
        setupLatex();
    }
}
