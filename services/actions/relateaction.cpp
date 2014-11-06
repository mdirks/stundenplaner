//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "relateaction.h"

RelateAction* RelateAction::instance = 0;

RelateAction::RelateAction()
{
}


RelateAction::~RelateAction()
{
}

RelateAction* RelateAction::getInstance()
{
	if( ! instance){
		instance = new RelateAction();
	}
	return instance;
}


/*!
    \fn RelateAction::relate(opo *op, stunde *st)
 */
bool RelateAction::relate(opo *op, stunde *st)
{
    st->addToOpos(op);
    return true;
}


/*!
    \fn RelateAction::relate(stunde *st, thema *th)
 */
bool RelateAction::relate(stunde *st, thema *th)
{
    st->setThema( th );
    return true;
}


/*!
    \fn RelateAction::relate(notiz *n, stunde *st)
 */
bool RelateAction::relate(notiz *n, stunde *st)
{
    st->addToNotizen(n);
}


/*!
    \fn RelateAction::relate(notiz *n, stunde *st)
 */
bool RelateAction::relate(stunde *st, klasse *kl)
{
    kl->addToStunden( st );
    return true;
}

/*!
    \fn RelateAction::relate(notiz *n, stunde *st)
 */
bool RelateAction::relate(PObject *o1, PObject *o2)
{
    qDebug("Relate PObjects: Do nothing !");
    if(o1->getClassName() == "schueler" && o2->getClassName() == "platz"){
	schueler *s = dynamic_cast<schueler*>(o1);
	platz *p = dynamic_cast<platz*>(o2);
	if(p) p->setSchueler(s);
	return true;
    } else {
	    return false;
    }
}

/*!
    \fn RelateAction::relate(platz *p, schueler *s)
 */
bool RelateAction::relate(schueler *s, platz *p)
{
    p->setSchueler(s);
    return true;
}
