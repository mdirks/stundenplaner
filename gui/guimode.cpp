#include "guimode.h"

#include "guirepository.h"

GuiMode::GuiMode(QString title)
    : QAction(title,0)
{
    connect(this,SIGNAL(triggered()),this,SLOT(doSetupMode()));
}

void GuiMode::doSetupMode()
{
    GuiRepository::getInstance()->setActiveMode(this);
}
