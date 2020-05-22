#include "mappinggeneratordialog.h"
#include "ui_mappinggeneratordialog.h"

#include "mappinggenerator.h"
#include "elementmodel.h"

#include <QFileDialog>
#include <QDebug>

MappingGeneratorDialog::MappingGeneratorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MappingGeneratorDialog),
    contextMenu(new QMenu(this)),
    domModel(new DomModel(QDomDocument()))
{
    ui->setupUi(this);

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));

    ui->buttonAddClass->setEnabled(false);
    ui->buttonAddBaseClass->setEnabled(false);
    ui->buttonGenerate->setEnabled(false);
    ui->buttonAddProperty->setEnabled(false);
    ui->buttonAddAsociation->setEnabled(false);
    ui->buttonAddReference->setEnabled(false);
}




void MappingGeneratorDialog::onCustomContextMenu(const QPoint &point)
{
    QModelIndex index = ui->treeView->indexAt(point);
    if (index.isValid()) {
        delete contextMenu;
        contextMenu=new QMenu(ui->treeView);

        contextMenu->addAction("Delete Element", this, SLOT(deleteElementSlot()));



        contextMenu->exec(ui->treeView->viewport()->mapToGlobal(point));
    }
}

void MappingGeneratorDialog::deleteElementSlot()
{
    if(!selectedNode.isNull()){
        QDomNode pNode=selectedNode.parentNode();
        pNode.removeChild(selectedNode);
        selectedNode=QDomElement();
    }
}

MGDAddNodeAction::MGDAddNodeAction(QModelIndex &i, QString &t)
    : ind(i), type(t)
{
    if (ind.isValid() && ind.row() % 2 == 0) {
        if(type.contains("persistence")){

        }


        //contextMenu->exec(ui->treeView->viewport()->mapToGlobal(point));
    }
}



MappingGeneratorDialog::~MappingGeneratorDialog()
{
    delete ui;
}

void MappingGeneratorDialog::chooseDesc()
{
    descFileName=QFileDialog::getOpenFileName(this, tr("Open File"),
                                              outDirName, tr("XML files (*.xml);;HTML files (*.html);;"
                                                          "SVG files (*.svg);;User Interface files (*.ui)"));
    if(!descFileName.isEmpty()){
        ui->labelDesc->setText(descFileName);
        QFile descFile(descFileName);
        if(descFile.open(QFile::ReadOnly | QFile::Text)){
            outDirName=QFileInfo(descFile).absolutePath();
            ui->labelOut->setText(outDirName);

            if(doc.setContent(&descFile)){
                /*
                DomModel *newModel=new DomModel(doc);
                ui->treeView->setModel(newModel);
                delete domModel;
                domModel=newModel;
                selectOk=true;
                */
                loadModelIntoTree();
            }
        }
    }
}

void MappingGeneratorDialog::loadModelIntoTree()
{
    DomModel *newModel=new DomModel(doc);
    ui->treeView->setModel(newModel);
    delete domModel;
    domModel=newModel;
    selectOk=true;
}


void MappingGeneratorDialog::chooseOut()
{
    qDebug() << "chooseOut()";
}

void MappingGeneratorDialog::accept()
{
    exit(1);
}

void MappingGeneratorDialog::generate()
{
    MappingGenerator *gen=new MappingGenerator();
    //gen->parse(descFileName,outDirName,outDirName);
    gen->setOutDirs(outDirName,outDirName);
    if(selectedNode.tagName().contains("class")){
        gen->handleClassElement(selectedNode);
    } else {
        qDebug()<<"Unable to handle other then class Elements";
    }

}

void MappingGeneratorDialog::saveToFile()
{
    QFile file(descFileName);
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for writing." );
        return;
    }
    QTextStream stream(&file);
    stream << doc.toString();
    file.close();
}

void MappingGeneratorDialog::addClass()
{
    QDomElement newNode=doc.createElement("class");
    newNode.setAttribute("name","");
    newNode.setAttribute("tname","");
    newNode.setAttribute("version","");

    selectedNode.appendChild(newNode);
    loadModelIntoTree();
}

void MappingGeneratorDialog::addBaseClass()
{
    QDomElement newNode=doc.createElement("baseclass");
    newNode.setAttribute("name","");

    selectedNode.appendChild(newNode);
    loadModelIntoTree();
}

void MappingGeneratorDialog::addProperty()
{
    QDomElement newNode=doc.createElement("property");
    selectedNode.appendChild(newNode);
    newNode.setAttribute("name","");
    newNode.setAttribute("type","");
    newNode.setAttribute("ctype","");
    newNode.setAttribute("cname","");
    newNode.setAttribute("getter","");
    newNode.setAttribute("setter","");

    selectedNode.appendChild(newNode);
    loadModelIntoTree();

}

void MappingGeneratorDialog::addAssociation()
{
    QDomElement newNode=doc.createElement("association");
    selectedNode.appendChild(newNode);

    newNode.setAttribute("name","");
    newNode.setAttribute("ascClass","");
    newNode.setAttribute("table","");
    newNode.setAttribute("priCol","");
    newNode.setAttribute("ascCol","");

    selectedNode.appendChild(newNode);
    loadModelIntoTree();

}

void MappingGeneratorDialog::addReference()
{
    QDomElement newNode=doc.createElement("reference");
    selectedNode.appendChild(newNode);

    newNode.setAttribute("name","");
    newNode.setAttribute("refClass","");
    newNode.setAttribute("table","");
    newNode.setAttribute("getter","");

    selectedNode.appendChild(newNode);
    loadModelIntoTree();

}

void MappingGeneratorDialog::newSelection(QModelIndex index)
{
    if (index.isValid() ) {
        DomModel *mod = static_cast<DomModel*>(ui->treeView->model());
        if(mod){
            QDomNode node=mod->node(index);
            selectedNode=node.toElement();
            QVariant nodeData = mod->data(index,0);
            if(nodeData.toString().contains("persistence")){
                ui->buttonAddClass->setEnabled(true);
                ui->buttonAddBaseClass->setEnabled(false);
                ui->buttonGenerate->setEnabled(false);
                ui->buttonAddProperty->setEnabled(false);
                ui->buttonAddAsociation->setEnabled(false);
                ui->buttonAddReference->setEnabled(false);
            } else if(nodeData.toString().contains("class")){
                ui->buttonAddClass->setEnabled(false);
                ui->buttonAddBaseClass->setEnabled(true);
                ui->buttonGenerate->setEnabled(true);
                ui->buttonAddProperty->setEnabled(true);
                ui->buttonAddProperty->setEnabled(true);
                ui->buttonAddReference->setEnabled(true);

            } else {
                ui->buttonAddClass->setEnabled(false);
                ui->buttonAddBaseClass->setEnabled(false);
                ui->buttonGenerate->setEnabled(false);

                ui->buttonAddProperty->setEnabled(false);
                ui->buttonAddProperty->setEnabled(false);
                ui->buttonAddReference->setEnabled(true);

            }
            QDomElement elm=selectedNode.toElement();
            if(!elm.isNull()){
                ui->listAtributes->setModel(new ElementModel(elm));
            }
        }


    }
}

QString MappingGeneratorDialog::HtmlFromXml(const QString &xmlFileName)
{
    QFile file(xmlFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cant open file: " << file.errorString();
        return "";
    }

    QDomDocument htmlDoc;
    QDomElement htmlRoot = htmlDoc.createElement("html");

    QDomDocument xmlDoc;
    xmlDoc.setContent(&file);
    QDomElement xmlRoot = xmlDoc.documentElement();
    QDomElement xmlItem = xmlRoot.firstChild().toElement();

    while(!xmlItem.isNull())
    {
        //read xml
        int itemId = xmlItem.attribute("id", "0").toInt();
        QString itemName = xmlItem.attribute("Name", "");

        QDomElement xmlImg = xmlItem.firstChild().toElement();
        QString imgSrc;
        int imgId = 0;
        if (!xmlImg.isNull()) {
            imgSrc = xmlImg.attribute("src", "");
            imgId = xmlImg.attribute("id", "0").toInt();
        }

        //create html
        QDomElement htmlItem = htmlDoc.createElement("p");

        QDomElement htmlImg = htmlDoc.createElement("img");
        htmlImg.setAttribute("src", imgSrc);

        QDomElement htmlText = htmlDoc.createElement("p");
        QDomText textName = htmlDoc.createTextNode(itemName);
        htmlText.appendChild(textName);

        htmlItem.appendChild(htmlImg);
        htmlItem.appendChild(htmlText);
        htmlRoot.appendChild(htmlItem);

        //next
        xmlItem = xmlItem.nextSibling().toElement();
    }

    htmlDoc.appendChild(htmlRoot);

    return htmlDoc.toString();
}


QString MappingGeneratorDialog::XmlFromHtml(const QString &strHtml)
{
    QDomDocument xmlDoc;
    QDomElement xmlRoot = xmlDoc.createElement("Stage");

    QDomDocument htmlDoc;
    htmlDoc.setContent(strHtml);
    QDomElement htmlRoot = htmlDoc.documentElement();
    QDomElement htmlHead = htmlRoot.firstChild().toElement();
    QDomElement htmlBody = htmlHead.nextSibling().toElement();

    int dummyId = 1;
    QDomElement htmlItem = htmlBody.firstChild().toElement();
    while (!htmlItem.isNull())
    {
        //<p><img/></p><p>text</p>
        QDomElement htmlImg = htmlItem.firstChild().toElement();
        QString imgSrc = htmlImg.attribute("src", "");

        htmlItem = htmlItem.nextSibling().toElement(); //move to <p> with text
        QDomText itemText = htmlItem.firstChild().toText();

        //create xml elements
        QDomElement xmlItem = xmlDoc.createElement("Item");
        xmlItem.setAttribute("id", dummyId);
        xmlItem.setAttribute("Name", itemText.data());

        QDomElement xmlImg = xmlDoc.createElement("image");
        xmlImg.setAttribute("src", imgSrc);
        xmlImg.setAttribute("id", dummyId);

        xmlItem.appendChild(xmlImg);
        xmlRoot.appendChild(xmlItem);

        //next
        htmlItem = htmlItem.nextSibling().toElement();
        dummyId++;
    }

    xmlDoc.appendChild(xmlRoot);
    return xmlDoc.toString();
}
