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
#include "mappinggenerator.h"

#include <string>

#include <QString>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QRegExp>
#include <QFileInfo>
#include <QDateTime>
#include <QDebug>


/**

*/
 int main(int argc, char** argv){
	QApplication a(argc,argv);
	
	MappingGenerator gen;
	if(argc < 4){
        qWarning("usage: MappingGenerator  xml-file include-dir source-dir");
		return -1;
	}

    QMessageBox::critical( 0, "Critical", QString("Directory is: ").append(QDir().absolutePath()));

	const char* fileName = argv[1];
	const char* includeDir = argv[2];  // 
	const char* srcDir = argv[3]; //where the class declarations live
	gen.parse(fileName, includeDir,srcDir);
	//generator.parse(argv[1]);
	return 0;
}


MappingGenerator::MappingGenerator() : declStream(), implStream()
{
}


MappingGenerator::~MappingGenerator()
{
}




/*!
    \fn MappingGenerator::parse(const QString fileName)
 */
void MappingGenerator::parse(const QString fileName, const QString includeDir, const QString srcDir)
{
    this->includeDir = includeDir;
    this->srcDir = srcDir;
    
    readDomDoc( fileName );
    
    QDomNodeList mainList = domDoc.elementsByTagName("persistence");
    if(mainList.count()>0){
    	  QDomElement mainElement=mainList.item(0).toElement();
	  packageName = mainElement.attribute("package");
    }
    
    
    classList = domDoc.elementsByTagName("class");
    for(int i=0; i<classList.count(); i++){
    	QDomElement classElement = classList.item(i).toElement();
        qDebug() << QString("Found class ").append(classElement.attribute("name"));
        handleClassElement(classElement);
    }
    
    createFactory();
    
}

/*!
    \fn MappingGenerator::readDomDoc(const String fileName)
 */
void MappingGenerator::readDomDoc(const QString fileName)
{
    QFile file( fileName );
    if ( !file.open( QIODevice::ReadOnly ) ) {
        QMessageBox::critical( 0, "Critical Error",
                QString( "Cannot open file %1" ).arg( fileName ) );
        return;
    }
    if ( !domDoc.setContent( &file ) ) {
        QMessageBox::critical( 0,  "Critiical Error" ,
                QString( "Parsing error for file %1" ).arg( fileName ) );
       file.close();
        return;
    }
    file.close();
}


void MappingGenerator::createFactory()
{
    qDebug() << QString("Writing factory:");
    QFile declFile( QString(packageName).toLower().append("objectfactory.h"));
    QFile implFile( QString(packageName).toLower().append("objectfactory.cpp"));
    
    
    if( ! (declFile.open( QIODevice::WriteOnly ) &  implFile.open( QIODevice::WriteOnly )) ){
    	QMessageBox::critical( 0, "Critical", "Could not open declaration and implementation files");
	return;
    }
    
    
    declStream_Factory.setDevice( &declFile );
    implStream_Factory.setDevice( &implFile );
   
    writeDeclaration_Factory(declStream);
    writeDefinition_Factory(implStream);
     
    declFile.close();
    implFile.close();



}

void MappingGenerator::writeDeclaration_Factory(QTextStream &declStream)
{
	   declStream << " //  \n \
// C++ Interface: stundepersistence \n \
//   \n \
// Description:  \n \
// \n \
// \n \
// Author: Marcus Dirks <mopp@suse>, (C) 2005 \n \
//  \n \
// Copyright: See COPYING file that comes with this distribution \n \
// \n \
// \n \
#ifndef "<< packageName << "OBJECTFACTORY_H \n \
#define "<< packageName << "OBJECTFACTORY_H \n \
\n \
#include \"" << includeDir << "/orm/persistence/pobject.h\" \n \
#include \"" << includeDir << "/orm/mapping/mappedobject.h\" \n\
\n\n\
class " << packageName << "ObjectFactory \n\
{\n\
public:\n";

	for(int i=0; i<classList.count(); i++){
    		QDomElement classElement = classList.item(i).toElement();
		className = classElement.attribute("name");
		declStream << "	" << className << "* create" << className << "();\n\
		void deleteObject(" << className << "* o)\n;";
	}
	
declStream << "\n\n };\n \
#endif\n";
}

void MappingGenerator::writeDefinition_Factory(QTextStream &implStream)
{
	implStream << "#include " << packageName << "objectfactory.h \n\n";
	
	for(int i=0; i<classList.count(); i++){
    		QDomElement classElement = classList.item(i).toElement();
		className = classElement.attribute("name");
		
		implStream << className << "*  " << packageName << "ObjectFactory::create" << className << "()\n\
		{\n\
			return " << className << "mapper::getInstance()->create();\n\
		}\n\n";
		
		implStream << "void " << packageName << "ObjectFactory::deleteObject(" << className << " *o)\n\
		{\n";
			ascNodeList = classElement.elementsByTagName("association");
			for(int i=0; i<ascNodeList.count(); i++){
				QDomElement ascElement = ascNodeList.item(i).toElement();
				if(ascElement.attribute("ascClass") == className){
					
				}
			}
		implStream << "}\n\n";
	}
}


QDomNodeList MappingGenerator::append(QDomNodeList list1, QDomNodeList list2)
{
    QDomDocument temporary("tempDoc");
    for(int i = 0 ; i < list1.count() ; i++)
    {
        temporary.appendChild(temporary.importNode(list1.at(i), true));
    }

    for(int i = 0 ; i < list2.count() ; i++)
    {
        temporary.appendChild(temporary.importNode(list2.at(i), true));
    }
    return temporary.childNodes();
}

/*!
    \fn MappingGenerator::handleClassElement(const QDomElement classElement)
 */
void MappingGenerator::handleClassElement(QDomElement classElement)
{
    for(int i=0; i<listBases.count(); i++){
    	QDomElement baseClassElement = listBases.item(i).toElement();
        QDomNodeList listChildren = baseClassElement.childNodes();
        for(int j=0; j<listChildren.count(); j++){
            QDomNode node = listChildren.item(j);
            classElement.appendChild(node);
        }
    }
    
    className = classElement.attribute("name");
    baseClassName = classElement.attribute("base");
    pClassName = classElement.attribute("name").append("mapper");
    tableName = classElement.attribute("tname");
    classVersion = classElement.attribute("version");
    
    ascNodeList = classElement.elementsByTagName("association");
    refNodeList = classElement.elementsByTagName("reference");
    propertyNodeList = classElement.elementsByTagName("property");
    //append properties of base class
    if(!baseClassName.isEmpty()){
        for(int i=0; i<classList.size(); i++){
            QDomNode node=classList.at(i);
            if(node.toElement().attribute("name")==baseClassName){
                baseClassElement=node.toElement();
                QString baseClassVersion=baseClassElement.attribute("version");
                classVersion.append("-").append(baseClassVersion);
                //ascNodeList = append(ascNodeList,baseClassElement.elementsByTagName("association"));
                //refNodeList = append(refNodeList,baseClassElement.elementsByTagName("reference"));
                propertyNodeList = append(propertyNodeList,baseClassElement.elementsByTagName("property"));

            }
        }
    }
    QDomNodeList listBases = classElement.elementsByTagName("baseclass");
    
    
    
    qDebug() << QString("\n ---------------------------------------------------- \n Handling class: ").append(className).append(QString("\n -------------------------------------------------------\n"));
    QFile declFile( QString(srcDir).append("/").append(QString(className).toLower()).append("mapper.h"));
    QFile implFile( QString(srcDir).append("/").append(QString(className).toLower()).append("mapper.cpp"));
    
    
    if( ! (declFile.open( QIODevice::WriteOnly ) &  implFile.open( QIODevice::WriteOnly )) ){
    	QMessageBox::critical( 0, "Critical", "Could not open declaration and implementation files");
	return;
    }
    
    
    declStream.setDevice( &declFile );
    implStream.setDevice( &implFile );
   
    qDebug() << QFileInfo(declFile).absoluteFilePath();
    writeDeclaration(declStream);
    writeDefinition(implStream);
     
    qDebug() << "Closing: ";
    declFile.close();
    qDebug() << "- Declaration";
    implFile.close();
   qDebug() << "- Definition \n ----------------------------------------------------------\n";
    
}


void MappingGenerator::writeDeclaration(QTextStream& declStream){
    qDebug() << "Writing declaration";

    QRegExp rx("*/");
    rx.setPatternSyntax(QRegExp::Wildcard);

    declStream << " //  \n \
// C++ Interface: stundepersistence \n \
//   \n \
// Description:  \n \
// \n \
// \n \
// Author: Marcus Dirks <mopp@suse>, (C) 2005 \n \
//  \n \
// Copyright: See COPYING file that comes with this distribution \n \
// \n \
// Written on " << QDateTime::currentDateTime().toString() << "\n\
// \n \
#ifndef "<< className << "MAPPER_H \n \
#define "<< className << "MAPPER_H \n \
\n \
#include \"" << "orm/persistence/pobject.h\" \n \
#include \"" << "orm/mapping/mappedobject.h\" \n\
#include \"" << "orm/mapping/association.h\" \n\
#include \"" << "orm/mapping/murl.h\" \n\
#include \"" << "orm/persistence/persistenceclass.h\" \n \
#include \"" <<  className.toLower() << ".h\" \n";
for(int i=0; i<ascNodeList.count();i++)
{
		QDomElement ascElement = ascNodeList.item(i).toElement();
        QString asc_class = ascElement.attribute("ascClass");
        QString asc_name = ascElement.attribute("name");

        declStream << "#include \"" << asc_class.toLower() << ".h\" \n";
}

for(int i=0; i<refNodeList.count();i++)
{
		QDomElement refElement = refNodeList.item(i).toElement();
        QString ref_class = refElement.attribute("refClass"); //.remove(QRegExp("*/"));
        QString ref_name = refElement.attribute("name");

        declStream << "#include \""  << ref_class.toLower() << ".h\" \n";
}

declStream << "#include \""  << "orm/mapping/abstractmapper.h\"\n \
#include \"" <<  "orm/persistence/variant.h\"\n \
#include \"" << "orm/repository/repositoryentryimpl.h\"\n \
#include \"" << "orm/repository/stringproperty.h\"\n \
#include \"" << "orm/repository/integerproperty.h\"\n \
#include \"" << "orm/repository/pobjectproperty.h\"\n \
#include \"" << "orm/repository/collectionpropertyimpl.h\"\n \
#include \"" << "orm/repository/numericproperty.h\"\n \
#include \"" << "orm/repository/dateproperty.h\"\n \
#include \"" << "orm/repository/booleanproperty.h\"\n \
#include \"" << "orm/repository/datetimeproperty.h\"\n \
#include \"" << "orm/repository/repositoryenabled.h\"\n ";
if(baseClassName != ""){
    declStream << "#include \"" << QString(baseClassName).toLower() << "mapper.h\"\n";
}
declStream << "\n \
/** \n \
@author Marcus Dirks \n \
*/ \n \
class " << className << "mapper : ";
if(baseClassName != ""){
              declStream << "public " << baseClassName.remove(rx) << "mapper \n";
} else {
	declStream << "public AbstractMapper, public RepositoryEnabled\n";
}
declStream << "{\n \
public:\n \
    static " << className << "mapper* getInstance();\n \
    ~" << className << "mapper();\n \
    static " << className << "* create();\n\
\n \
    string getTableName();\n \
    string getClassName();\n \
    string* getColumnTypes();\n \
    string* getColumns();\n \
    string* getValues(PObject* realSubject);\n \
    int getColumnCount();\n \
    void save();\n \
    void save(PObject *realSubject);\n \
    PObject* createNewObject();\n \
    list<" << className << "*>* find();\n\
    void init(PObject* o, Variant* res);\n\
    RepositoryEntry *getRepositoryEntry();\n\n";
    
    

    for(int i=0; i<ascNodeList.count();i++)
	{
		QDomElement ascElement = ascNodeList.item(i).toElement();
        //QString asc_class = ascElement.attribute("ascClass").remove(QRegExp(".*/"));
        QString asc_class = ascElement.attribute("ascClass").remove(rx).remove(rx);

        QString asc_name = ascElement.attribute("name");

        declStream << "  list<" << asc_class << "*> * find" << asc_name << "(int pri_id);\n";
        declStream << "  list<" << asc_class << "*> * find" << asc_name << "(int pri_id,string prop,string value);\n";
	}
	


     for(int i=0; i<refNodeList.count();i++)
	{
		QDomElement refElement = refNodeList.item(i).toElement();
        //QString ref_class = refElement.attribute("refClass").remove(QRegExp("*/"));
        QString ref_class = refElement.attribute("refClass").remove(rx);

        QString ref_name = refElement.attribute("name");

		declStream <<  ref_class << " * find" << ref_name << "(int pri_id);\n";
	}	
	
    declStream << "\nprotected:\n \
    " << className << "mapper();\n \
\n \
private:\n \
   static " << className << "mapper* instance;\n \
\n\n";
   
   declStream << "   string *columnTypes;\n \
   string *columns;\n ";
   
   for(int i=0; i<ascNodeList.count();i++){
   	QDomElement ascElement = ascNodeList.item(i).toElement();
    QString asc_class = ascElement.attribute("ascClass").remove(rx);
    QString asc_name = ascElement.attribute("name");
	
	declStream << " Association<" <<  className << ", " << asc_class << "> *asc_" << asc_name << ";\n";
   }
   
   declStream << "  \n \
\n \
};\n \
\n \
#endif\n \ 
";
qDebug() << QString("Declaration done !");
}   


/*!
    \fn MappingGenerator::writeDefinition(QTextStream &implStream, QString className)
 */
void MappingGenerator::writeDefinition(QTextStream &implStream)
{
    qDebug() << QString("Writing Definition (%1)").arg(className);
    propertyCount = propertyNodeList.count();
    
    property = new QString[propertyCount];
    propertyTyp = new QString[propertyCount];
    columnName = new QString[propertyCount];
    columnTyp = new QString[propertyCount];
    propertySetter = new QString[propertyCount];
    propertyGetter = new QString[propertyCount];
    argTypSetter = new QString[propertyCount];
    
    for(int i=0; i<propertyCount; i++){
    	QDomElement propertyElement = propertyNodeList.item(i).toElement();
	property[i] = propertyElement.attribute("name");
	propertyTyp[i] = propertyElement.attribute("type");
	columnName[i] = propertyElement.attribute("cname");
	columnTyp[i] = propertyElement.attribute("ctype");
	propertyGetter[i] = propertyElement.attribute("getter");
	if(propertyGetter[i]==""){
		propertyGetter[i] = QString("get%1").arg(property[i]);
	}
	propertySetter[i] = propertyElement.attribute("setter");
	if(propertySetter[i]==""){
		propertySetter[i] = QString("set%1").arg(property[i]);
	}
	argTypSetter[i] = propertyElement.attribute("setterArgTyp");
    }

    //qDebug(QString("Column count : %1 ").arg(propertyCount));
    
    //qDebug("Intro");
    writeDefinition_Intro();
    //qDebug("Constructor");
    writeDefinition_Constructor();
    //qDebug("createNewObject");
    writeDefinition_createNewObject();
    //qDebug("create");
    writeDefinition_create();
    //qDebug("stdGetters");
    writeDefinition_stdGetters();
    //qDebug("getValues");
    writeDefinition_getValues();
    //qDebug("save");
    writeDefinition_save();
    //qDebug("init");
    writeDefinition_init();
    //qDebug("find");
    writeDefinition_find();
    //qDebug("findAssociation");
    writeDefinition_findAssociations();
    //qDebug("getRepositoryEntry");
    writeDefinition_repository();
    
    
    delete[] property;
    delete[] propertySetter;
    delete[] propertyGetter;
    delete[] argTypSetter;    
    
}

    
void MappingGenerator::writeDefinition_Intro()
{ 
    implStream << "// \n \
// C++ Implementation: " << pClassName << "\n \
//\n \
// Description: \n \
//\n \
//\n \
// Author: Marcus Dirks <mopp@suse>, (C) 2005\n \
//\n \
// Copyright: See COPYING file that comes with this distribution\n \
//\n \
//\n \
#include \""<< pClassName.toLower() << ".h\"\n \
#include \"" << "services/utils/utils.h\"\n \
#include \"" << className.toLower() << ".h\"\n\
#include \"" << "orm/persistence/database.h\"\n \
#include \"" << "orm/repository/urlproperty.h\"\n \
//#include \"" << "orm/mappingproperty.h\"\n\
\n \
"<< pClassName <<"* "<< pClassName << "::instance=0;\n \
\n \
" << pClassName << "* " << pClassName << "::getInstance()\n \
{\n \
	if(!instance){\n \
		instance=new " << pClassName << "();\n \
	}\n \
	return instance;\n \
}\n\n\n ";
}

void MappingGenerator::writeDefinition_Constructor()
 {
   implStream  << pClassName <<"::" << pClassName << "()\n \
 {\n \
	version = \"" << classVersion << "\";\n\
	columns = new string[" << propertyCount << "];\n \
	columnTypes = new string[" << propertyCount << "];\n ";
	
    qDebug() <<QString("propertyCount : %1").arg(propertyCount);
	
	for(int i=0; i<propertyCount; i++){
        qDebug() << QString("Property %1").arg(i);
		implStream << "	columns[" << i << "] = \"" << columnName[i] << "\";\n \
	columnTypes[" << i << "] = \"" << columnTyp[i] << "\";\n" ;
		implStream << "	mapProperties[\"" << columnName[i] << "\"] = new Property(\"" << columnName[i] << "\");\n"; 
	}
	
    QRegExp rx("*/");
    rx.setPatternSyntax(QRegExp::Wildcard);
	for(int i=0; i<ascNodeList.count();i++)
	{
		QDomElement ascElement = ascNodeList.item(i).toElement();
        QString table = ascElement.attribute("table");
        QString pri_col = ascElement.attribute("priCol");
        QString asc_col = ascElement.attribute("ascCol");
        QString asc_class = ascElement.attribute("ascClass").remove(rx);
        QString asc_name = ascElement.attribute("name");
        QString adder = ascElement.attribute("adder");
		if(adder == "") adder = "addTo" + asc_name;
        QString deleter = ascElement.attribute("deleter");
		if(deleter == "") deleter = "deleteFrom" + asc_name;
		
		

		implStream << "asc_" << asc_name << " = new Association<" << className << ", " << asc_class << ">(\"" << table << "\",\"" << pri_col << "\",\"" << asc_col << "\",\""
<< asc_class << "\", &" << className << "::" << adder << ", &" << className << "::" << deleter << ");\n";
	        implStream << "mapAssociations[\"" << asc_name << "\"] = asc_" << asc_name << ";\n";
		implStream << "registerAssociation( asc_" << asc_name << ");\n";

	}
	
	for(int i=0; i<refNodeList.count();i++)
	{
		QDomElement refElement = refNodeList.item(i).toElement();
        QString ref_class = refElement.attribute("refClass").remove(QRegExp("*/"));
        QString ref_name = refElement.attribute("name");
        QString ref_zus = refElement.attribute("zusatz");

		if(ref_zus != ""){
			implStream << "mapReferences[\"" << ref_name << "\"] = new Reference(\"" << className << "\",\"" <<  ref_class << "\" , \"" << ref_zus <<  "\");\n";
		} else {
			implStream << "mapReferences[\"" << ref_name << "\"] = new Reference(\"" << className << "\",\"" <<  ref_class << "\");\n";
		}
		
	}
	
	implStream << "}\n\n\n" << pClassName << "::~" << pClassName << "(){}\n\n\n ";
}



void MappingGenerator::writeDefinition_stdGetters()
 {
    implStream << "string " << pClassName << "::getTableName()\n \
{\n \
    return string(\"" << tableName << "\");\n \
}\n \
\n \
string " << pClassName << "::getClassName()\n \
{\n \
	return string(\"" << className <<"\");\n \
}\n \
\n \
string* " << pClassName << "::getColumnTypes()\n \
{\n \
	return columnTypes;\n \
}\n \
\n \
string* " << pClassName << "::getColumns()\n \
{\n \
	return columns;\n \
}\n \
\n \
int " << pClassName << "::getColumnCount()\n \
{\n \
    return " << propertyCount << ";\n \
}\n\n\n ";
}

void MappingGenerator::writeDefinition_find()
{

	implStream << "list<" << className << " *>*" << pClassName << "::find() \n \
{\n \
	return (list <" << className << "*>*) Database::getInstance()->getAll(this); \n\
}\n\n\n";

}

void MappingGenerator::writeDefinition_findAssociations()
{
	
    QRegExp rx("*/");
    rx.setPatternSyntax(QRegExp::Wildcard);
	for(int i=0; i<ascNodeList.count();i++)
	{
		QDomElement ascElement = ascNodeList.item(i).toElement();
        QString table = ascElement.attribute("table");
        QString pri_col = ascElement.attribute("priCol");
        QString asc_col = ascElement.attribute("ascCol");
        QString asc_class = ascElement.attribute("ascClass").remove(rx);
        QString asc_name = ascElement.attribute("name");

		implStream << "list<" << asc_class << "*> * " << pClassName << "::find" << asc_name << "(int pri_id) \n \
{ \n \
	return asc_" << asc_name << " ->  findAssociates( pri_id );\n \
    }\n\n\n";

        implStream << "list<" << asc_class << "*> * " << pClassName << "::find" << asc_name << "(int pri_id,string prop,string value) \n \
        { \n \
            return asc_" << asc_name << " ->  findAssociates( pri_id,prop,value);\n \
            }\n\n\n";
	}

}

void MappingGenerator::writeDefinition_getValues() 
{
   implStream << "string* " << pClassName << "::getValues(PObject *realSubject)\n \
{\n \
	string *values = new string[" << propertyCount << "];  \n \
	"<< className << " *o = (" << className << "*) realSubject;\n";
	
	for(int i=0; i<propertyCount; i++){
	 	implStream <<  "	values[" << i << "] = to_string(o->" << propertyGetter[i] << "());\n" ;
	}
	
	implStream << "return values;\n \
}\n\n\n ";
}



void MappingGenerator::writeDefinition_save()
{
	implStream << "void " << pClassName << "::save(){\n";
	implStream << "qWarning(\"" << className << ": save() not implemented\");\n";
implStream << "}\n\
\n\
void " << pClassName << "::save(PObject *realSubject)\n";
implStream << "{\n \t" << className << " *o = (" << className << "*) realSubject;\n\n\
    Database *db = Database::getInstance();\n";
implStream << "    db->save(realSubject);\n";

       for(int i=0; i<ascNodeList.count();i++)
	{
		QDomElement ascElement = ascNodeList.item(i).toElement();
        QString table = ascElement.attribute("table");
        QString pri_col = ascElement.attribute("priCol");
        QString asc_col = ascElement.attribute("ascCol");
        QString asc_class = ascElement.attribute("ascClass");
        QString asc_name = ascElement.attribute("name");

  		implStream << "	asc_" << asc_name << " -> save(realSubject, o->get" << asc_name << "() );\n\n";

	}
	for(int i=0; i<refNodeList.count();i++)
	{
		QDomElement refElement = refNodeList.item(i).toElement();
        QString ref_name = refElement.attribute("name");
		
		implStream << "	mapReferences[ \"" << ref_name << "\" ] -> save(realSubject, (PObject*) o->get" << ref_name << "());\n";
	}

	if(baseClassName != ""){
		implStream << "	" << baseClassName << "mapper::save(realSubject);\n";
	}
	
	
   implStream <<  "}\n\n\n" ;  //close written function
   
}


void MappingGenerator::writeDefinition_createNewObject()
{
   implStream  << "PObject* " << pClassName << "::createNewObject()\n \
{\n \
    return new " << className << "();\n \
}\n\n\n ";
}

void MappingGenerator::writeDefinition_create()
{
   implStream << className << "* " << pClassName << "::create()\n \
{\n \
    return  (" << className << "*) AbstractMapper::create( " << pClassName << "::getInstance() );\n \
}\n\n\n ";
}

void MappingGenerator::writeDefinition_init()
{
   implStream << "void " << pClassName << "::init(PObject* inito, Variant *res)\n \
{\n \
	" << className << " *o = (" << className << "*) inito;\n";
	
	for(int i=0; i<propertyCount; i++){
  		//implStream << "	o->" << propertySetter[i] << "((" << propertyTyp[i] << ") res[" << i << "]);\n ";
		implStream << "	o->" << propertySetter[i] << "( res[" << i << "].as" << propertyTyp[i] << "());\n ";
	}
	implStream << "	inito->init();\n";
    	

	implStream << "}\n\n\n ";
} 



void MappingGenerator::writeDefinition_repository()
{
	implStream << "RepositoryEntry* " << pClassName << "::getRepositoryEntry()\n \
	{\n \
	RepositoryEntry* entry = new RepositoryEntryImpl( \"" << className << "\" ); \n";
		

		implStream << "	entry->addProperty( new StringProperty<" << className << ">(\"Name\", \"string\", &" << className << "::getName, &" << className << "::setName, false) );\n";

		 for(int i=0; i<propertyNodeList.count();i++)
		{
			QDomElement propElement = propertyNodeList.item(i).toElement();
            QString name = propElement.attribute("name");
            QString type = propElement.attribute("type");
            QString ctype = propElement.attribute("ctype");
            QString getterName = propertyGetter[i];//propElement.attribute("getter");
            QString setterName = "&" + className + "::" + propertySetter[i];// propElement.attribute("setter");
			
			if(type=="int" || type=="double"){
				implStream << "	entry->addProperty( new NumericProperty< " << type << "," << className << "> ( \"" << name << "\", \"" << type << "\" , &" << className << "::"  <<
getterName << "," << setterName << " ) ); \n";
			} else if (type == "bool"){ 
				implStream << "	entry->addProperty( new BooleanProperty< "  << className << "> ( \"" << name << "\", \"" << type << "\" , &" << className << "::"  <<
getterName << "," << setterName << " ) ); \n";
			} else if (type == "string"){
				implStream << "	entry->addProperty( new StringProperty< " << className << " >( \"" << name << "\" , \"" << type << "\", &" << className << "::"  << getterName ;
				if(setterName != ""){
					implStream << ", " << setterName;
				} else {
					implStream << ", 0";
				}
				if(ctype == "text"){
					implStream << ", true";
				} else {
					implStream << ", false";
				}
				implStream << " ) );\n";
			} else if (type == "QDate"){
				implStream << "	entry->addProperty( new DateProperty< " << className << "> ( \"" << name << "\", \"" << type << "\" , &" << className << "::"  <<
getterName << ", " << setterName << " ) ); \n";
			} else if (type == "QDateTime"){
				implStream << "	entry->addProperty( new DateTimeProperty< " << className << "> ( \"" << name << "\", \"" << type << "\" , &" << className << "::"  <<
getterName << ", " << setterName << " ) ); \n";
            } else if (type == "MUrl") {
                implStream << "	entry->addProperty( new UrlProperty< " << className << "> ( \"" << name << "\", \"" << type << "\" , &" << className << "::"  <<
getterName << ", " << setterName << " ) ); \n";
            } else if (type == "QFile"){
				/** \todo Handle QFile (writing FileProperty etc)*/
				/*
				implStream << "	entry->addProperty( new DateProperty< " << className << "> ( \"" << name << "\", \"" << type << "\" , &" << className << "::"  <<
getterName << ", " << setterName << " ) ); \n";
				*/
			}else {
                 qDebug() << QString("Could not add RepositoryProperty for property of Type ").append(type);
			}
		}
		
		
		for(int i=0; i<ascNodeList.count();i++)
		{
			QDomElement ascElement = ascNodeList.item(i).toElement();
            QString name = ascElement.attribute("name");
            QString type = ascElement.attribute("ascClass").remove(QRegExp("^([a-z]+/)+"));
            QString getterName = QString("get") + name; //ascElement.attribute("getter");
            QString adderName = QString("addTo") + name;
            QString removerName = className + "::" + QString("deleteFrom") + name;

			implStream << "	entry->addProperty( new CollectionPropertyImpl<" << type << "," << className << ">( \"" << name << "\" , \"" << type << "\", &" << className << "::"  <<
getterName << ", &" << className << "::" << adderName <<", &" << removerName << "  ) ); \n";
		}
		
		for(int i=0; i<refNodeList.count();i++)
		{
			QDomElement refElement = refNodeList.item(i).toElement();
            QString name = refElement.attribute("name");
            QString type = refElement.attribute("refClass").remove(QRegExp("^([a-z]+/)+"));
            QString getterName = QString("get") + name; //refElement.attribute("getter");
            QString setterName = QString("set") + name;
			
			implStream << "	entry->addProperty( new PObjectProperty<" << type << "," << className << ">( \"" << name << "\" , \"" << type << "\", &" << className << "::"  <<
getterName << "," << "&" << className << "::" <<  setterName << " ) ); \n";
		}
		
		if(baseClassName != ""){
			implStream << "	entry->registerBase( \"" << baseClassName << "\" );\n";
		}

		implStream << "	return entry;\n }\n";
}


