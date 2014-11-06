//
// C++ Implementation: textpropertyeditordialog
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "textpropertyviewer.h"
#include "qlayout.h"
#include "qmessagebox.h"
#include "orm/transactions/transactions.h"
#include <ktrader.h>
#include <klibloader.h>
#include <kprocess.h>
#include <krun.h>
#include <poppler-qt4.h>
#include <QDebug>
#include <QKeyEvent>
#include <QScrollArea>
#include <QChar>
#include <QSizePolicy>

QString TextPropertyViewer::StandardHeader = QString("\\documentclass[12pt]{article} \\pagestyle{empty}"
                                                        "\\usepackage{ngerman} "
                                                       "\\oddsidemargin -1cm \n \\topmargin -3.0cm"
                                                       "\\textheight 28cm \\textwidth 18.0cm"
                                                        "\\parindent=0pt \\parskip=0.15 true in"
                                                       "\\begin{document}\\sffamily\n");

QString TextPropertyViewer::StandardFooter = QString("\n\\end{document}");

TextPropertyViewer::TextPropertyViewer(PObject *parent, QString dT, QWidget *pw) :
    QWidget(pw), header(StandardHeader), footer(StandardFooter), tmpDir(QDir::current().path() + QDir::separator() + "tmp")
{
	this->parent = parent;
	this->prop=0;
	displayString=dT;


    label = new TextPropertyLabel(this);
    editor = new TextPropertyEditor(parent,dT,this);
    editor->setMinimumHeight(10);


    stack= new QStackedWidget(this);
    QVBoxLayout *l = new QVBoxLayout(this);
    l->addWidget(stack);
    stack->addWidget(label);
    stack->addWidget(editor);

	connect(label, SIGNAL(editRequested()), this, SLOT(editVorn()));
    connect(this, SIGNAL(applyRequested()), this, SLOT(stopEdit()));

	if (!tmpDir.exists())
                if (!tmpDir.mkdir(tmpDir.path()))
      			{
        			QMessageBox::warning(this, "Cannot make directory", "Could not create directory ");
                }
    stack->setCurrentWidget(label);
	editing=false;
	label->setFocus();	

	compileVorn(true);

}

TextPropertyViewer::TextPropertyViewer(PObject *parent, RepositoryProperty *prop, QWidget *pw) :
    QWidget(pw), header(StandardHeader), footer(StandardFooter), tmpDir(QDir::current().path() + QDir::separator() + "tmp")
{
	this->parent = parent;
	this->prop = prop;
	displayString=QString("Shouldnt be used");

    editor = new TextPropertyEditor(parent,prop,0);
    label = new TextPropertyLabel(this);


    stack= new QStackedWidget(this);
    QVBoxLayout *l = new QVBoxLayout(this);
    l->addWidget(stack);
    stack->addWidget(label);
    stack->addWidget(editor);

	connect(label, SIGNAL(editRequested()), this, SLOT(editVorn()));
    connect(this, SIGNAL(applyRequested()), this, SLOT(stopEdit()));

	if (!tmpDir.exists())
                if (!tmpDir.mkdir(tmpDir.path()))
      			{
        			QMessageBox::warning(this, "Cannot make directory", "Could not create directory ");
			}

    stack->setCurrentWidget(label);
	editing=false;

    //todo label->setFocusPolicy(QWidget::StrongFocus);
	label->setFocus();	

    if(parent){
        compileVorn(true);
    }
}

void TextPropertyViewer::setParentObject(PObject *o)
{
   this->parent = o;
   editor->setParentObject(o);
   compileVorn(true);

}

void TextPropertyViewer::setHeader(QString h)
{
    this->header=h;
}

void TextPropertyViewer::setFooter(QString f)
{
    this->footer=f;
}


TextPropertyEditorDialog::TextPropertyEditorDialog(PObject *parent, QString displayString, QWidget *pw) :
    KDialog(pw)
{
    setButtons(Apply|Close);
	setInitialSize(QSize(700,500));
	QWidget *displayWidget = new QWidget(this);
    QGridLayout *displayLayout = new QGridLayout(displayWidget);

	viewer = new TextPropertyViewer(parent,displayString,displayWidget);
	title = new QLabel(displayWidget);
	//title->setText(prop->getName());
	
	displayLayout->addWidget(title,0,0);
	displayLayout->addWidget(viewer,1,0);


	setMainWidget(displayWidget);
	displayWidget->show();
}


TextPropertyEditorDialog::TextPropertyEditorDialog(PObject *parent, RepositoryProperty *prop, QWidget *pw) :
    KDialog(pw)
{
    setButtons(Apply|Close);
    setInitialSize(QSize(700,500));
	
	
	QWidget *displayWidget = new QWidget(this);
    QGridLayout *displayLayout = new QGridLayout(displayWidget);

    viewer = new TextPropertyViewer(parent,prop,displayWidget);
	title = new QLabel(displayWidget);
    title->setText(prop->getName().c_str());
	
	displayLayout->addWidget(title,0,0);
	displayLayout->addWidget(viewer,1,0);


    setMainWidget(displayWidget);
	displayWidget->show();

	
		
}



TextPropertyViewer::~TextPropertyViewer()
{
}

TextPropertyEditorDialog::~TextPropertyEditorDialog()
{
}

QString TextPropertyViewer::getFileName()
{
    return tmpDir.filePath(QString("%1%2.pdf").arg(parent->getID()).arg(prop->getName().c_str()));
}

void TextPropertyViewer::setHidden(bool h)
{
    hidden=h;
}

void TextPropertyViewer::setFitToView(bool f)
{
    fit=f;
    QSizePolicy policy=QSizePolicy();
    policy.setHeightForWidth(true);
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    policy.setHorizontalPolicy(QSizePolicy::Ignored);
    setSizePolicy(policy);
}

void TextPropertyViewer::readVorn()
{	
    if(hidden || !parent){
        displayPm = QPixmap();
        label->setPixmap(QPixmap());
    } else {
        QString fileName = getFileName();
		Poppler::Document *doc = Poppler::Document::load(fileName);
        if(doc && doc->page(0)){
            doc->setRenderHint(Poppler::Document::TextAntialiasing);
            doc->setRenderHint(Poppler::Document::Antialiasing);
            QImage image = doc->page(0)->renderToImage();
            if(!image.isNull()){
                displayPm=QPixmap::fromImage(image);
                /*
                if(fit){
                    displayPm=displayPm.scaledToWidth(this->width());
                }
                */
                label->setPixmap(displayPm);
                if(fit){
                    resize(displayPm.size());
                }
            } else {
                label->setText("Failed to read image");
            }
        } else {
            label->setText(QString("Failed to load  %1 !").arg(fileName));

        }
    }

}

void TextPropertyViewer::setScrollBarPolicy(Qt::ScrollBarPolicy policy){
    label->setVerticalScrollBarPolicy(policy);
    label->setHorizontalScrollBarPolicy(policy);
}

void TextPropertyViewer::editVorn()
{
        /*
        label->hide();
        editor->startEdit();
        editor->show();
		editor->setFocus();
        */
    stack->setCurrentWidget(editor);
		editing = true;
}

void TextPropertyViewer::stopEdit()
{
	editor->stopEdit();
	compileVorn(true);
    //editor->hide();
    readVorn();
    stack->setCurrentWidget(label);
	editing = false;
}

void TextPropertyEditorDialog::stopEdit()
{
	viewer->stopEdit();
}

void TextPropertyViewer::compileFinished(int code, QProcess::ExitStatus exitStatus)
{
    qDebug() << QString("Compile finished with code %1").arg(code);
    readVorn();
}

void TextPropertyViewer::compileError( QProcess::ProcessError error)
{
    qDebug() << QString("Compile Error %1").arg(error);
}

 QString TextPropertyViewer::getCompileStringVorn()
{
     QString fileName = getFileName();

   QFile texFile(fileName);
    if(!texFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        return "Failed to open file";
    }
    QTextStream stream(&texFile);
    stream << header;
    /*
    stream << "\\documentclass[12pt]{article} \\pagestyle{empty}";
    stream << "\\usepackage{ngerman} ";
    stream <<  "\\oddsidemargin -1cm \n \\topmargin -3.0cm";
    stream << "\\textheight 28cm \\textwidth 18.0cm";
    stream << "\\parindent=0pt \\parskip=0.15 true in";
    stream << "\\begin{document}\\sffamily\n";
    */
    if(prop){
        stream << prop->asString(parent).c_str();
    } else {
        stream << displayString;
    }

    stream << footer;
    //stream << "\n\\end{document}";

    return fileName;

}



void TextPropertyViewer::compileVorn(bool reload)
{
    if(!parent) return;

    QString prog=QString("pdflatex");
    QStringList args;
    args << QString("-output-directory=%1").arg(tmpDir.path());
    //args << QString("-jobname=%1").arg(parent->getID());
    args << getCompileStringVorn();

    p  = new QProcess(this);

    p->setStandardErrorFile(QString("/home/mopp/err%2.txt").arg(parent->getID()),
                            QIODevice::Append);
    p->setStandardOutputFile(QString("/home/mopp/out%2.txt").arg(parent->getID()),
                            QIODevice::Append);

    qDebug() << prog << args;
    if(reload){
        connect(p,SIGNAL(finished(int, QProcess::ExitStatus)),
                this,SLOT(compileFinished(int,QProcess::ExitStatus)));
        connect(p,SIGNAL(error( QProcess::ProcessError)),
                this,SLOT(compileError( QProcess::ProcessError)));
    }

    p->start(prog,args);
    if(!p->waitForStarted()){
        qDebug() << "Process could not be started";
    }


    //p->waitForFinished();


}




void TextPropertyEditorDialog::display(QString displayText, PObject *parent)
{
	TextPropertyEditorDialog *instance = new TextPropertyEditorDialog(parent, displayText);
	instance->exec();
}




void TextPropertyEditorDialog::edit(RepositoryProperty *prop, PObject *parent)
{
	Transactions::getCurrentTransaction()->add(parent);
	TextPropertyEditorDialog *instance = new TextPropertyEditorDialog(parent, prop);
	instance->exec();
	instance->stopEdit();
}

void TextPropertyViewer::keyPressEvent ( QKeyEvent * e )
{
    qDebug() << "TextPropertyEditorDialog::keyPressEvent ";
	if(editing){
        if (e->key() == Qt::Key_F2){
            qDebug() << "TextPropertyEditorDialog::keyPressEvent : F2 -> applyRequested";
				stopEdit();
				emit applyRequested();
		} else {
            qDebug() << QString("TextPropertyEditorDialog::keyPressEvent unknown key %1,%2").arg(e->text()).arg(e->key());
			//emit applyRequested();
		}
	} else {
        //label->emitEditRequested();
        QWidget::keyPressEvent(e);
	}
}
// void TextPropertyEditorDialog::stopEdit()
// {
// 	if(editor){
// 		editor->stopEdit();
// 	}
// }

void TextPropertyViewer::resizeEvent(QResizeEvent *e)
{

    if(fit){
        QSize eventSize=e->size();
        //QPixmap copy = displayPm.scaledToWidth(eventSize.width());
        //QSize originalSize=displayPm.size();
        //displaySize = copy.size();
        //label->setPixmap(copy);


        //if(this->size().height()!=displaySize.height()){
        //    if(displaySize.width()>0){
                //label->resize(eventSize);
                editor->resize(eventSize);
                //resize(displaySize);
        //    }
        //}

    }
}

QSize TextPropertyViewer::sizeHint()
{
    if(fit){
        return label->size();
    } else {
        return QWidget::sizeHint();
    }
}


TextPropertyLabel::TextPropertyLabel(QWidget *parent, const char *name)
    : QScrollArea(parent)
{
    label = new QLabel(this);


    setWidget(label);

}

void TextPropertyLabel::mouseDoubleClickEvent ( QMouseEvent * e )
{
	qDebug("TextPropertyLabel::mouseDoubleClickEvent");
	emit(editRequested());
}



void TextPropertyLabel::setText(QString s)
{
	label->setText(s);
}



void TextPropertyLabel::setPixmap(QPixmap pm)
{
    label->resize(pm.size());
    label->setPixmap(pm);
}


// void TextPropertyLabel::mousePressEvent ( QMouseEvent * e )
// {
// 	
// 	if(e->button() == Qt::LeftButton){
// 		//emit(nextRequested());
// 	} else if (e->button() == Qt::RightButton){
// 		emit(switchRequested());
// 	} else {
// 		e->ignore();
// 	}
// 	
// }
// 
// void TextPropertyLabel::keyPressEvent ( QKeyEvent * e )
// {
// 	qDebug("TextPropertyLabel::keyPressEvent ");
// 	if(e->key() == Qt::Key_Space || e->key() == Qt::Key_Down){
// 		emit nextRequested();
// 	} else if( e->key() == Qt::Key_Right || e->key() == Qt::Key_Left){
// 		emit switchRequested();
// 	} else if( e->key() == Qt::Key_Return) {
// 		emit editRequested();
// 	}
// }

/*!
    \fn TextPropertyLabel::emitEditRequested()
 */
void TextPropertyLabel::emitEditRequested()
{
    emit editRequested();
}
