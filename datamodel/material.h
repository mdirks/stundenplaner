q/***************************************************************************
                          material.h  -  description
                             -------------------
    begin                : Sam Feb 28 2004
    copyright            : (C) 2004 by Marcus Dirks
    email                : marcus.dirks@web.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MATERIAL_H
#define MATERIAL_H


#include <string>

#include <qstring.h>
#include <qfile.h>

#include "orm/transactions/transactionobject.h"

using namespace std;

/**
  *@author Marcus Dirks
  */

class material : public TransactionObject
{
public: 
    material();
    string getTitle();
    void setTitle(string title);
    string getFileName();
    void setFileName(string filename);

    QFile* getFile();
    void setFile(QFile* file);

    void init();

    string getName(); //override for PObject

private: // Public attributes
  string title, filename;
  QFile *file;
     
};

#endif
