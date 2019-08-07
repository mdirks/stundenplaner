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
#include "transactionobject.h"

TransactionObject::TransactionObject()
{
	is_saved=false;
	is_new=false;
	is_deleted = false;
}


TransactionObject::~TransactionObject()
{
}




/*!
    \fn TransactionObject::markNew()
 */
void TransactionObject::markNew()
{
    is_deleted=true;
}


/*!
    \fn TransactionObject::markModified()
 */
void TransactionObject::markModified()
{
    is_modified=true;
}


/*!
    \fn TransactionObject::markDeleted()
 */
void TransactionObject::markDeleted()
{
    is_deleted=true;
}


/*!
    \fn TransactionObject::markSaved()
 */
void TransactionObject::markSaved()
{
    is_saved=true;
}


/*!
    \fn TransactionObject::isModified()
 */
bool TransactionObject::isModified()
{
   return is_modified;
}


/*!
    \fn TransactionObject::isNew()
 */
bool TransactionObject::isNew()
{
    return is_new;
}


/*!
    \fn TransactionObject::isSaved()
 */
bool TransactionObject::isSaved()
{
    return is_saved;
}


/*!
    \fn TransactionObject::isDeleted()
 */
bool TransactionObject::isDeleted()
{
    return is_deleted;
}
