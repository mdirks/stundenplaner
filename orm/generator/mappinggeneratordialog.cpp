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
    ui->buttonAddProperty->setEnabled(false);
    ui->buttonAddProperty->setEnabled(false);
}




void MappingGeneratorDialog::onCustomContextMenu(const QPoint &point)
{
    QModelIndex index = ui->treeView->indexAt(point);
    if (index.isValid() && index.row() % 2 == 0) {
        delete contextMenu;
        contextMenu=new QMenu(ui->treeView);
        QVariant nodeData = ui->treeView->model()->data(index,0);
        if(nodeData.toString().contains("persistence")){
            contextMenu->addAction("Add class", this, SLOT(addClassSlot()));
        }


        contextMenu->exec(ui->treeView->viewport()->mapToGlobal(point));
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
                DomModel *newModel=new DomModel(doc);
                ui->treeView->setModel(newModel);
                delete domModel;
                domModel=newModel;
                selectOk=true;
            }
        }
    }
}

void MappingGeneratorDialog::chooseOut()
{
    qDebug() << "chooseOut()";
}

void MappingGeneratorDialog::accept()
{
    MappingGenerator *gen=new MappingGenerator();
    gen->parse(descFileName,outDirName,outDirName);
}

void MappingGeneratorDialog::addClass()
{
    QDomElement newNode=doc.createElement("class");
    selectedNode.appendChild(newNode);
}

void MappingGeneratorDialog::addProperty()
{
    QDomElement newNode=doc.createElement("property");
    selectedNode.appendChild(newNode);
}

void MappingGeneratorDialog::addAsociation()
{
    QDomElement newNode=doc.createElement("class");
    selectedNode.appendChild(newNode);
}


void MappingGeneratorDialog::newSelection(QModelIndex index)
{
    if (index.isValid() ) {
        DomModel *mod = static_cast<DomModel*>(ui->treeView->model());
        if(mod){
            selectedNode=mod->node(index);
            QVariant nodeData = mod->data(index,0);
            if(nodeData.toString().contains("persistence")){
                ui->buttonAddClass->setEnabled(true);
                ui->buttonAddProperty->setEnabled(false);
                ui->buttonAddProperty->setEnabled(false);
            } else if(nodeData.toString().contains("class")){
                ui->buttonAddClass->setEnabled(false);
                ui->buttonAddProperty->setEnabled(true);
                ui->buttonAddProperty->setEnabled(true);
            } else {
                ui->buttonAddClass->setEnabled(false);
                ui->buttonAddProperty->setEnabled(false);
                ui->buttonAddProperty->setEnabled(false);
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
