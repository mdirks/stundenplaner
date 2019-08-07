/***************************************************************************
                          material.cpp  -  description
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

#include "material.h"
#include "materialmapper.h"

#include <QFileInfo>
//Del von KDevelop:material::material(){
//Del von KDevelop:}
//Del von KDevelop:material::~material(){
//Del von KDevelop:}

#define DEFAULT_NAME "test.sdtpl"
/*!
    \fn material::material()
 */
 material::material() : filename(DEFAULT_NAME)
{
    setMapper(materialmapper::getInstance());

}

void material::init()
{
	//this-> file = new QFile(filename);
}


void material::setTitle(string title){
	this->title=title;
}

string material::getTitle()
{
	return title;
}

void material::setFile(QFile *file){
	this->file=file;
}

QFile* material::getFile()
{
	if(file==0){
        file = new QFile(getFileName().c_str());
	}
	return file;
}

void material::setFileName(string filename){
	this->filename=filename;
	//qDebug(QString("Setting filename to %1").arg(filename));
	
	if(file){
		//delete file;
		file=0;
	}

}

string material::getFileName()
{
	return filename;
}

string material::getName()
{
    if(PObject::getName().empty() || PObject::getName() == "Unknown")
    {
        QFileInfo info(*getFile());
        return info.fileName().toStdString();
    } else {
        return PObject::getName();
    }
}
