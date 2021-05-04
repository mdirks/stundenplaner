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
//#include <ktrader.h>
//#include <klibloader.h>
//#include <kprocess.h>
//#include <krun.h>
#include <poppler-qt5.h>
#include <QDebug>
#include <QKeyEvent>
#include <QScrollArea>
#include <QChar>
#include <QSizePolicy>
#include <QPainter>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QMenu>

QString TextPropertyLabel_pdf::StandardHeader = QString("\\documentclass[12pt]{article} \\pagestyle{empty}"
                                                        "\\usepackage{ngerman} "
                                                        "\\usepackage[utf8]{inputenc}"
                                                       "\\oddsidemargin -1cm \n \\topmargin -3.0cm"
                                                       "\\textheight %1cm \\textwidth %2cm"
                                                        "\\parindent=0pt \\parskip=0.15 true in"
                                                       "\\begin{document}\\sffamily\n");

QString TextPropertyLabel_pdf::StandardFooter = QString("\n\\end{document}");

TextPropertyViewer::TextPropertyViewer(QWidget *pw, TextPropertyViewer::Type t) :
    QWidget(pw)
{
    this->parent=0;
    this->prop=0;


    doCommonSetup(t);
}

/*
TextPropertyViewer::TextPropertyViewer(PObject *parent, QString dT, QWidget *pw) :
    QWidget(pw)
{
	this->parent = parent;
	this->prop=0;
	displayString=dT;

    doCommonSetup();

}
*/


TextPropertyViewer::TextPropertyViewer(PObject *parent, RepositoryProperty *prop, QWidget *pw, double w, double h,
                                       TextPropertyViewer::Type t)
    : QWidget(pw)
{
	this->parent = parent;
	this->prop = prop;



    doCommonSetup(t);

}


void TextPropertyViewer::doCommonSetup(TextPropertyViewer::Type t)
{

    //label->setFrameStyle(QFrame::NoFrame);

    if(prop){
        if(t == PdfLabel){
            label = new TextPropertyLabel_pdf(parent,prop,this);
        } else {
            label = new TextPropertyLabel_md(parent,prop,this);
        }
        editor = new TextPropertyEditor(parent,prop,this);
    } else {
        if(t == PdfLabel){
            label = new TextPropertyLabel_pdf(this);
        } else {
            label = new TextPropertyLabel_md(this);
        }
        editor = new TextPropertyEditor(this);
    }
    editor->setFrameStyle(QFrame::NoFrame);
    hidden=false;
    fit=false;

    stack= new QStackedWidget(this);
    stack->setFrameStyle(QFrame::NoFrame);
    stack->setContentsMargins(0,0,0,0);

    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    l->setSpacing(0);
    l->addWidget(stack);
    stack->addWidget(label);
    stack->addWidget(editor);

    connect(label, SIGNAL(editRequested()), this, SLOT(editVorn()));
    connect(this, SIGNAL(applyRequested()), this, SLOT(stopEdit()));


    stack->setCurrentWidget(label);
    editing=false;
    label->setFocus();
    label->read();



}



TextPropertyLabel_md::TextPropertyLabel_md(QWidget *parent, const char *name)
    : TextPropertyLabel(parent,name), m_viewer(new QLabel /*QTextEdit(parent)*/)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    m_viewer->setFrameStyle(QFrame::NoFrame);
    m_viewer->setAlignment(Qt::AlignTop);
    l->addWidget(m_viewer);

}

TextPropertyLabel_md::TextPropertyLabel_md(PObject *o, RepositoryProperty *prop, QWidget *parent, const char *name)
    : TextPropertyLabel(o,prop,parent,name), m_viewer(new QLabel /*new QTextEdit(parent)*/)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    m_viewer->setFrameStyle(QFrame::NoFrame);
    m_viewer->setAlignment(Qt::AlignTop);
    l->addWidget(m_viewer);
}


void TextPropertyLabel_md::compileVorn(bool reload)
{
    read();
}


void TextPropertyLabel_md::read()
{
    QString text=prop->asString(parent).c_str();
    m_viewer->setText(text);
}


TextPropertyLabel_pdf::TextPropertyLabel_pdf(QWidget *parent, const char *name)
    : TextPropertyLabel(parent,name),twidth(-1.0), theight(-1.0),
       tmpDir(QDir::current().path() + QDir::separator() + "tmp"), m_viewer(new PdfViewer(this)),
      displayString("Shouldnt be used")
{
    header=StandardHeader;
    footer=StandardFooter;

    QVBoxLayout *l = new QVBoxLayout(this);
    m_viewer->setFrameStyle(QFrame::NoFrame);
    l->addWidget(m_viewer);

     if (!tmpDir.exists() && !tmpDir.mkdir(tmpDir.path()))
     {
          QMessageBox::warning(this, "Cannot make directory", "Could not create directory ");
     }



}

TextPropertyLabel_pdf::TextPropertyLabel_pdf(PObject *o, RepositoryProperty *prop, QWidget *parent, const char *name)
    : TextPropertyLabel(o,prop,parent,name),theight(-1.0), twidth(-1.0),
      tmpDir(QDir::current().path() + QDir::separator() + "tmp"), m_viewer(new PdfViewer(this)),
      displayString("Shouldnt be used")
{
    header=StandardHeader;
    footer=StandardFooter;

     QVBoxLayout *l = new QVBoxLayout(this);
     m_viewer->setFrameStyle(QFrame::NoFrame);
     l->addWidget(m_viewer);

     //setMinimumHeight(10);

     if (!tmpDir.exists() && !tmpDir.mkdir(tmpDir.path()))
     {
          QMessageBox::warning(this, "Cannot make directory", "Could not create directory ");
     }



}


void TextPropertyViewer::setParentObject(PObject *o)
{
   this->parent = o;
   editor->setParentObject(o);
   label->setParentObject(o);
   label->compileVorn(true);

}

void TextPropertyViewer::setProperty(RepositoryProperty *p)
{
    this->prop = p;
    editor->setProperty(p);
}

void TextPropertyLabel::setHeader(QString h)
{
    this->header=h;
}

void TextPropertyLabel::setFooter(QString f)
{
    this->footer=f;
}


/*
TextPropertyEditorDialog::TextPropertyEditorDialog(PObject *parent, QString displayString, QWidget *pw) :
    QDialog(pw)
{
    //ToDo: does chooser show up, add to layout ?
    //setButtons(Apply|Close);
    //setInitialSize(QSize(700,500));
	QWidget *displayWidget = new QWidget(this);
    QGridLayout *displayLayout = new QGridLayout(displayWidget);

	viewer = new TextPropertyViewer(parent,displayString,displayWidget);
	title = new QLabel(displayWidget);
	
	displayLayout->addWidget(title,0,0);
	displayLayout->addWidget(viewer,1,0);


    //setMainWidget(displayWidget);
	displayWidget->show();
}
*/


TextPropertyEditorDialog::TextPropertyEditorDialog(PObject *parent, RepositoryProperty *prop, QWidget *pw) :
    QDialog(pw)
{
    //ToDo: does chooser show up, add to layout ?
    //setButtons(Apply|Close);
    //setInitialSize(QSize(700,500));
	
	
	QWidget *displayWidget = new QWidget(this);
    QGridLayout *displayLayout = new QGridLayout(displayWidget);

    viewer = new TextPropertyViewer(parent,prop,displayWidget);
	title = new QLabel(displayWidget);
    title->setText(prop->getName().c_str());
	
	displayLayout->addWidget(title,0,0);
	displayLayout->addWidget(viewer,1,0);


    //setMainWidget(displayWidget);
	displayWidget->show();

	
		
}



TextPropertyViewer::~TextPropertyViewer()
{
}

TextPropertyEditorDialog::~TextPropertyEditorDialog()
{
}

QString TextPropertyLabel_pdf::getTexFileName()
{
    if(prop && parent){
        return tmpDir.filePath(QString("%1%2.tex").arg(parent->getID()).arg(prop->getName().c_str()));
    } else if(parent) {
        return tmpDir.filePath(QString("%1.tex").arg(parent->getID()));
    } else {
        return "nani.pdf";
    }
}

QString TextPropertyLabel_pdf::getFileName()
{
    if(prop && parent){
        return tmpDir.filePath(QString("%1%2.pdf").arg(parent->getID()).arg(prop->getName().c_str()));
    } else if(parent) {
        return tmpDir.filePath(QString("%1.pdf").arg(parent->getID()));
    } else {
        return "nani.pdf";
    }
}

void TextPropertyViewer::setHidden(bool h)
{
    hidden=h;
}

/*
void TextPropertyViewer::setZoomFactor(double f)
{
    label->setZoomFactor(f);
}
*/

/*
void TextPropertyViewer::setResizePolicy(bool res)
{
    label->setResizePolicy(res);
}
*/

void TextPropertyViewer::setFitToView(bool f)
{
    fit=f;
    QSizePolicy policy=QSizePolicy();
    policy.setHeightForWidth(true);
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    setSizePolicy(policy);
}

void TextPropertyLabel_pdf::read()
{	
    QString fileName = getFileName();
    m_viewer->loadNewFile(fileName);
}

void TextPropertyViewer::print()
{
       QPrinter printer;
       //QPrinter printer(QPrinter::HighResolution);

       QPrintDialog printDialog(&printer);
       if (printDialog.exec() == QDialog::Accepted) {
            QPainter painter;
            painter.begin(&printer);
            painter.drawPixmap(0,0,displayPm);
            painter.end();
       }

}

void TextPropertyViewer::contextMenuEvent(QContextMenuEvent *e)
{
    const QPoint p=mapToGlobal(e->pos());
    QMenu *pmenu = new QMenu();
    pmenu->addAction("Drucken",this,SLOT(print()));

    pmenu->popup(p);
    e->accept();

}



void TextPropertyViewer::setScrollBarPolicy(Qt::ScrollBarPolicy policy){
    //label->setVerticalScrollBarPolicy(policy);
    //label->setHorizontalScrollBarPolicy(policy);
}

void TextPropertyViewer::editVorn()
{
    stack->setCurrentWidget(editor);
    editor->setFocus();
    editing = true;
}

void TextPropertyViewer::stopEdit()
{
	editor->stopEdit();
    label->compileVorn(true);
    //editor->hide();
    label->read();
    stack->setCurrentWidget(label);
	editing = false;
    editor->clearFocus();
}

void TextPropertyEditorDialog::stopEdit()
{
	viewer->stopEdit();
}

void TextPropertyLabel::compileFinished(int code, QProcess::ExitStatus exitStatus)
{
    qDebug() << QString("Compile finished with code %1").arg(code);
    read();
}

void TextPropertyLabel::compileError( QProcess::ProcessError error)
{
    qDebug() << QString("Compile Error %1").arg(error);
}

QString TextPropertyLabel_pdf::getCompileStringVorn()
{
    double cheight, cwidth;
    if(theight<0 || twidth<0){
     cheight=this->size().width()/50*5;
     cwidth=this->size().width()/50-.5;
   } else {
        cheight=theight;
        cwidth=twidth;
    }
   QString fileName = getTexFileName();

   QFile texFile(fileName);
    if(!texFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        return "Failed to open file";
    }
    QTextStream stream(&texFile);
    stream << header.arg(cheight).arg(cwidth);

    if(prop && parent){
        stream << prop->asString(parent).c_str();
    } else {
        stream << displayString;
    }

    stream << footer;
    //stream << "\n\\end{document}";

    return fileName;

}



void TextPropertyLabel_pdf::compileVorn(bool reload)
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



/*
void TextPropertyEditorDialog::display(QString displayText, PObject *parent)
{
	TextPropertyEditorDialog *instance = new TextPropertyEditorDialog(parent, displayText);
	instance->exec();
}
*/




void TextPropertyEditorDialog::edit(RepositoryProperty *prop, PObject *parent)
{
	Transactions::getCurrentTransaction()->add(parent);
	TextPropertyEditorDialog *instance = new TextPropertyEditorDialog(parent, prop);
	instance->exec();
	instance->stopEdit();
}

void TextPropertyViewer::keyPressEvent ( QKeyEvent * e )
{
    qDebug() << "TextPropertyViewer::keyPressEvent ";
	if(editing){
        if (e->key() == Qt::Key_F2){
            qDebug() << "TextPropertyViewer::keyPressEvent : F2 -> applyRequested";
				stopEdit();
				emit applyRequested();
		} else {
            qDebug() << QString("TextPropertyEditorDialog::keyPressEvent unknown key %1,%2").arg(e->text()).arg(e->key());
		}
    } else if(e->key() == Qt::Key_F2){
        label->emitEditRequested();
    } else {
        e->ignore();
    }
}

void TextPropertyLabel::keyPressEvent ( QKeyEvent * e )
{
    qDebug() << "TextPropertyLabel::keyPressEvent ";
}


void TextPropertyViewer::resizeEvent(QResizeEvent *e)
{

    if(fit){
        QSize eventSize=e->size();
        editor->resize(eventSize);
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


TextPropertyLabel::TextPropertyLabel(QWidget *pw, const char *name)
    : QWidget(pw), header(""), footer("")
{

}

TextPropertyLabel::TextPropertyLabel(PObject *po, RepositoryProperty *p, QWidget *pw, const char *name)
    : QWidget(pw),
      parent(po), prop(p), header(""), footer("")
{

}


void TextPropertyLabel::mouseDoubleClickEvent ( QMouseEvent * e )
{
	qDebug("TextPropertyLabel::mouseDoubleClickEvent");
	emit(editRequested());
}





/*!
    \fn TextPropertyLabel::emitEditRequested()
 */
void TextPropertyLabel::emitEditRequested()
{
    emit editRequested();
}
