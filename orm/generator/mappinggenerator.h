//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MAPPINGGENERATOR_H
#define MAPPINGGENERATOR_H

#include <QDomDocument>
#include <QString>
#include <QTextStream>
#include <QWidget>







/** Generates a concrete mapper for persistent classes as defined in persistence.xml.


	Methods generated include :

		-  save(PObject *realSubject) : 
			- db->save(realSubject) (relies on getColumns(), getValues()) 
			- asc_... -> save(realSubject, o->get...() )
			- ref_... -> save(realSubject, o->get...())

		- getValues() :
			




@author Marcus Dirks
*/
class MappingGenerator : QWidget{
public:
    MappingGenerator();

    ~MappingGenerator();
    void parse(const QString fileName, const QString includeDir, const QString srcDir);
    void readDomDoc(const QString fileName);
    void setOutDirs(const QString includeDir, const QString srcDir);
    void handleClassElement(const QDomElement classElement);


protected:
    QDomDocument  domDoc;
private:
    void writeDeclaration(QTextStream &declStream);
    void writeDefinition(QTextStream &implStream);
    
    void createFactory();
    void writeDeclaration_Factory(QTextStream &declStream);
    void writeDefinition_Factory(QTextStream &implStream);
    
    
    void writeDefinition_Intro() ;
    void writeDefinition_Constructor();
    void writeDefinition_stdGetters();
    void writeDefinition_getValues() ;
    void writeDefinition_save() ;
    void writeDefinition_createNewObject() ;
    void writeDefinition_create();
    void writeDefinition_init(); 
    void writeDefinition_find(); 
    void writeDefinition_findAssociations();
    void writeDefinition_repository();
    

    QDomNodeList append(QDomNodeList list1, QDomNodeList list2);

private:  
    QTextStream declStream, implStream, declStream_Factory, implStream_Factory;
    QString className, baseClassName, pClassName, tableName, classVersion, packageName;

    QString *property, *propertyTyp, *propertySetter, *propertyGetter, *argTypSetter,*columnName,*columnTyp;
    int propertyCount;    
    
    QDomNodeList classList, ascNodeList, refNodeList, propertyNodeList, listBases;
    QDomElement baseClassElement;

    QString includeDir, srcDir;
    
};

#endif
