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
#include "objectfactory.h"
#include "objectfactoryimpl.h"

ObjectFactory* ObjectFactory::instance = 0;


ObjectFactory* ObjectFactory::getInstance()
{
	if( !  instance ){
		instance = new ObjectFactoryImpl();
	}
	return instance;
}