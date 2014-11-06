#include "modeplanung.h"
#include "gui/base/guiconfig.h"
#include "gui/base/doublepane.h"
#include "gui/guirepository.h"
#include "services/skalender.h"
#include "datamodel/stundenplaneintrag.h"
#include "gui/forms/pobjecteditor3.h"

#include <QIcon>
#include <QLabel>

ModePlanung* ModePlanung::instance=0;


ModePlanung::ModePlanung() :
    GuiMode("Planung")
{
    QPixmap pm = GuiConfig::getInstance()->getIcon("ModePlanung");
    if(pm.isNull()){
        GuiConfig::getInstance()->selectIcon("ModePlanung");
        pm = GuiConfig::getInstance()->getIcon("ModePlanung");
    }
    setIcon(pm);


    dp=0;

}

ModePlanung* ModePlanung::getInstance()
{
    if(instance==0)
    {
        instance=new ModePlanung();
    }
    return instance;
}

void ModePlanung::showForm(QWidget *w)
{
    if(dp){
        dp->showFormAtBottom(w);
    }
}

void ModePlanung::setupMode()
{
    GuiRepository *rep=GuiRepository::getInstance();
    QStackedWidget *sw=rep->getCentralWidget();

    rep->setActiveMode(this);
    QSplitter *spl = new QSplitter(Qt::Horizontal,sw);
    if(dp==0){

        dp = new DoublePane();
        spl->addWidget(dp);
        spl->addWidget(new QLabel("Empty"));

        sw->addWidget(spl);
        dp->showFormAtTop(rep->getFormForObject(SKalender::getInstance(),dp));
    }
    sw->setCurrentWidget(spl);


}

void ModePlanung::activateObject(PObject *o)
{
    if(stundenplaneintrag *se = dynamic_cast<stundenplaneintrag*>(o))
    {
        if(klasse *kl = se->getKlasse()){
            QWidget *editor=GuiRepository::getInstance()->getFormForObject(se,dp);
            sitzplan *sp = kl->getSitzplan();
            if(sp){
                QWidget *w = GuiRepository::getInstance()->getFormForObject(sp,editor);
                if(PObjectEditor3 *e = dynamic_cast<PObjectEditor3*>(editor)){
                    e->addEditor(w, "Sitzplan");
                }
            }
            dp->showFormAtBottom(editor);
        }
    }
}
