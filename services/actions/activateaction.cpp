
#include "activateaction.h"

ActivateAction* ActivateAction::instance=0;

ActivateAction::ActivateAction()
{
}


ActivateAction::~ActivateAction()
{
}

ActivateAction* ActivateAction::getInstance()
{
	if(instance){
		instance=new ActivateAction();
	}
	return instance;
}

void ActivateAction::activateObject(PObject *o)
{
	/*
	if(material *m = dynamic_cast<material*>(o)){
			new KRun(m->getFile()->name());
	} 
	RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry(o);
	RepositoryProperty *rp = re-> getMainProperty();
	if(rp){
		TextPropertyEditorDialog::edit(rp,o);
	} else {
		GuiRepository::getInstance()->showFormForObject(o);
	}
	*/


}
