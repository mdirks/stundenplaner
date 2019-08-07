#ifndef ACTIVATEACTION_H
#define ACTIVATEACTION_H

#include "qobject.h"
#include "orm/persistence/pobject.h"

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class ActivateAction : public QObject {
Q_OBJECT
private:
    ActivateAction();
    ~ActivateAction();

public:
    static ActivateAction* getInstance();
    void activateObject(PObject *o);

private:
	static ActivateAction *instance;
};

#endif
