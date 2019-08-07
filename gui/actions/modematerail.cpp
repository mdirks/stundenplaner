#include "modematerail.h"
#include "gui/guirepository.h"
#include "gui/base/guiconfig.h"
#include "gui/actions/guicreateaction.h"
#include "orm/repository/repository.h"

#include <QStackedWidget>
#include <QSplitter>
#include <QTextStream>
#include <QVBoxLayout>

ModeMaterial* ModeMaterial::instance=0;

ModeMaterial::ModeMaterial()
    : GuiMode("Material"),
      ui(new Ui::ModeMaterial)
{

    QPixmap pm = GuiConfig::getInstance()->getIcon("ModeMaterial");
    setIcon(pm);

    //editor = new QTextEdit();
    //viewer = new PdfViewer();
    toolBar=0;
    activeMaterial=0;
    //splitter=0;
    displayWidget=0;


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
    //guirep->setActiveMode(this);
    QStackedWidget *sw=guirep->getCentralWidget();

    if(!displayWidget){
        displayWidget=new QWidget(sw);
        ui->setupUi(displayWidget);
        //displayWidget->show();
        sw->addWidget(displayWidget);

        ui->viewSaetze->setObjectListProvider(new MapperListProvider("materialsatz"));

        connect(ui->viewSaetze,SIGNAL(currentChanged()),this,SLOT(changeSatz()));
        connect(ui->viewMaterialien,SIGNAL(currentChanged()),this,SLOT(changeMaterial()));
    }

    sw->setCurrentWidget(displayWidget);

    RepositoryProperty *rp= Repository::getInstance()->getRepositoryEntry("materialsatz")->getProperty("Materialien");
    prov = new RpListProvider(rp);




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

void ModeMaterial::changeMaterial()
{
    PObject *o = ui->viewMaterialien->getCurrent();
    if(material *m=dynamic_cast<material*>(o)){
        open(m);
    }
}

void ModeMaterial::changeSatz()
{
    if(prov){
        PObject *o=ui->viewSaetze->getCurrent();
        if(o){
            prov->setParentObject(o);
            ui->viewMaterialien->setObjectListProvider(prov);
            ui->viewMaterialien->setCurrentRow(0);
        }
    }
}



void ModeMaterial::setupLatex()
{
    ui->editor->clear();
    ui->viewer->close();
    QFile *f=activeMaterial->getFile();
    f->open(QIODevice::ReadOnly);
    QTextStream in(f);
    ui->editor->setText(in.readAll());
    f->close();
}

void ModeMaterial::setupTxt()
{
    ui->editor->clear();
    ui->viewer->close();
    QFile *f=activeMaterial->getFile();
    f->open(QIODevice::ReadOnly);
    QTextStream in(f);
    ui->editor->setText(in.readAll());
    f->close();
}

void ModeMaterial::setupPdf()
{
    ui->editor->clear();
    ui->viewer->loadNewFile(activeMaterial->getFileName().c_str());
}

void ModeMaterial::setupJap()
{
    genericSetup();
}


void ModeMaterial::genericSetup()
{
    ui->editor->clear();
    ui->viewer->close();
    QFile *f=activeMaterial->getFile();
    f->open(QIODevice::ReadOnly);
    QTextStream in(f);
    ui->editor->setText(in.readAll());
    f->close();
}

void ModeMaterial::tearDownMode()
{
    if(toolBar) toolBar->hide();
}


void ModeMaterial::open(material *m)
{
    activeMaterial=m;
    QFile *f = activeMaterial->getFile();
    if(f->fileName().contains(".tex")){
        setupLatex();
    } else if(f->fileName().contains(".txt")){
        setupTxt();
    } else if(f->fileName().contains(".pdf")){
        setupPdf();
    } else if(f->fileName().contains(".jap")){
        setupJap();
    }

}

void ModeMaterial::save()
{
    if(activeMaterial){
        QFile *f=activeMaterial->getFile();
        f->open(QIODevice::WriteOnly);
        QTextStream out(f);
        out << ui->editor->toPlainText() << endl;
        f->close();
    }

}

void ModeMaterial::createNew()
{
    PObject *o =  GuiCreateAction::getInstance()->create("material");
    activeMaterial = dynamic_cast<material*>(o);
    if(activeMaterial){
        open(activeMaterial);
    }
}
