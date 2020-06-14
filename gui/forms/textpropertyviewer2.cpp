#include "textpropertyviewer2.h"

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

#include "gui/base/guiconfig.h"
#include "services/mail/smtp.h"


QString TextPropertyViewer2::StandardHeader = QString("\\documentclass[12pt]{article} \\pagestyle{empty}"
                                                        "\\usepackage{ngerman} "
                                                       "\\oddsidemargin -1cm \n \\topmargin -3.0cm"
                                                       "\\textheight %1cm \\textwidth %2cm"
                                                        "\\parindent=0pt \\parskip=0.15 true in"
                                                       "\\begin{document}\\sffamily\n");

QString TextPropertyViewer2::StandardFooter = QString("\n\\end{document}");

TextPropertyViewer2::TextPropertyViewer2(QWidget *pw) :
    QWidget(pw), header(StandardHeader), footer(StandardFooter),
    tmpDir(QDir::current().path() + QDir::separator() + "tmp"), bgColor(Qt::lightGray)
{
    this->parent=0;
    this->prop=0;
    this->displayString="";

    doCommonSetup();
}

TextPropertyViewer2::TextPropertyViewer2(PObject *parent, QString dT, QWidget *pw) :
    QWidget(pw), header(StandardHeader), footer(StandardFooter),
    tmpDir(QDir::current().path() + QDir::separator() + "tmp"), bgColor(Qt::lightGray)
{
    this->parent = parent;
    this->prop=0;
    displayString=dT;
    name=parent->getName().c_str();
    doCommonSetup();

}

TextPropertyViewer2::TextPropertyViewer2(PObject *parent, RepositoryProperty *prop, QWidget *pw, double w, double h) :
    QWidget(pw), header(StandardHeader), footer(StandardFooter),
    tmpDir(QDir::current().path() + QDir::separator() + "tmp"),bgColor(Qt::lightGray),width(w), height(h)
{
    this->parent = parent;
    this->prop = prop;
    displayString=QString("Shouldnt be used");
    if(parent){
        name=parent->getName().c_str();
        if(prop){
            name.append(prop->getName().c_str());
        }
    }

    doCommonSetup();

}

TextPropertyViewer2::~TextPropertyViewer2()
{
}

void TextPropertyViewer2::doCommonSetup()
{
    publishAction = new QAction(GuiConfig::getInstance()->getIcon("publishAction"), "Publish",this);
    connect(publishAction,&QAction::triggered,this,&TextPropertyViewer2::publish);

    label = new PdfViewer(this);
    label->setMinimumWidth(200);
    label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    label->addContextMenuAction(publishAction);

    if(prop){
        editor = new TextPropertyEditor(parent,prop,this);
    } else {
        editor = new TextPropertyEditor(this);
    }
    editor->setFrameStyle(QFrame::NoFrame);
    hidden=false;
    fit=false;

    splitter = new QSplitter(Qt::Vertical,this);

    splitter->addWidget(label);
    splitter->addWidget(editor);

    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    l->setSpacing(0);
    l->addWidget(splitter);
    setLayout(l);


    input.mathmode = " ... ";
    input.dpi = 150;
    KLFBackend::klfSettings settings;
    if(!KLFBackend::detectSettings(&settings)) {
        qDebug() << "unable to find LaTeX in default directories.";
    } else {
        qDebug() << "default settings working!";
    }
    settings.epstopdfexec="/usr/bin/epstopdf";
    settings.pdflatex="/usr/bin/pdflatex";
    settings.outputType="PdfPage";
    mPreviewBuilderThread = new KLFPreviewBuilderThread(this, input, settings);

    connect(editor, SIGNAL(textChanged()), this,
        SLOT(updatePreview()), Qt::QueuedConnection);
    connect(mPreviewBuilderThread, SIGNAL(previewPdfAvailable(const QByteArray&, bool)),
            this, SLOT(showPreview(const QByteArray&, bool)), Qt::QueuedConnection);
}

void TextPropertyViewer2::updatePreview()
{
    // in linux, I need to reinstate the preamble when rendering. No idea why.
    input.preamble = QString("\\usepackage{amssymb,amsmath} "
                             "\\usepackage[whole]{bxcjkjatype}"
                             "\\usepackage{hyperref}");
    if(parent){
        input.latex = QString("{\\bf ").append(parent->getName().c_str()).append("}\\\\[.3cm]\\hrule ").toUtf8();
    }
    input.latex = input.latex.append(editor->toPlainText().toUtf8());
    if(mPreviewBuilderThread->inputChanged(input)) {
        qDebug() << "input changed. Render...";
        //ui->statusBar->showMessage("Input changed. Render...");

        //drop for the moment: slashes bug to time-consuming
        mPreviewBuilderThread->start();
  }
}


void TextPropertyViewer2::showPreview(const QByteArray& pdfData, bool latexerror)
{
    if (latexerror) {
      qDebug()<<"Unable to render your equation. Please double check.";

    } else {
      currentPdfData=pdfData;
      label->loadNewData(pdfData,name);
    }
}

void TextPropertyViewer2::publish()
{
    Smtp* smtp = new Smtp("marcus.dirks", "tomoko-web", "smtp.web.de", 587);
    //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    smtp->sendMail("marcus_dirks.30c4795@m.evernote.com", "" /*ui->rcpt->text()*/ ,
                        "Notiz", "Notiz", currentPdfData );
}


void TextPropertyViewer2::setParentObject(PObject *o)
{
   this->parent = o;
   editor->setParentObject(o);
   //compileVorn(true);
}

void TextPropertyViewer2::setProperty(RepositoryProperty *p)
{
    this->prop = p;
    editor->setProperty(p);
}

void TextPropertyViewer2::setHeader(QString h)
{
    this->header=h;
}

void TextPropertyViewer2::setFooter(QString f)
{
    this->footer=f;
}

void TextPropertyViewer2::setBackgroundColor(QColor c)
{
    bgColor=c;
}


void TextPropertyViewer2::setHidden(bool h)
{
    hidden=h;
}

void TextPropertyViewer2::setZoomFactor(double f)
{
    qDebug() << "WARNING TextPropertyViewer2::setZoomFactor : do nothing";
    //label->setZoomFactor(f);
}

void TextPropertyViewer2::setResizePolicy(bool res)
{
    qDebug() << "WARNING TextPropertyViewer2::setResizePolicy : do nothing";
    //label->setResizePolicy(res);
}

void TextPropertyViewer2::setFitToView(bool f)
{
    fit=f;
    QSizePolicy policy=QSizePolicy();
    policy.setHeightForWidth(true);
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    setSizePolicy(policy);
}

/*
void TextPropertyViewer2::readVorn()
{
    if(hidden || !parent){
        //displayPm = QPixmap();
        //label->setPixmap(QPixmap());
    } else {
        QString fileName = getFileName();
        label->loadNewFile(fileName);

    }

}
*/

void TextPropertyViewer2::print()
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

void TextPropertyViewer2::contextMenuEvent(QContextMenuEvent *e)
{
    const QPoint p=mapToGlobal(e->pos());
    QMenu *pmenu = new QMenu();
    pmenu->addAction("Drucken",this,SLOT(print()));

    pmenu->popup(p);
    e->accept();

}



void TextPropertyViewer2::setScrollBarPolicy(Qt::ScrollBarPolicy policy){
    //label->setVerticalScrollBarPolicy(policy);
    //label->setHorizontalScrollBarPolicy(policy);
}

/*
void TextPropertyViewer2::editVorn()
{
       //stack->setCurrentWidget(editor);
        editing = true;
}
*/

void TextPropertyViewer2::stopEdit()
{
    editor->stopEdit();
    editing = false;
}

void TextPropertyViewer2::keyPressEvent ( QKeyEvent * e )
{
    qDebug() << "TextPropertyViewer2::keyPressEvent ";
    if(editing){
        if (e->key() == Qt::Key_F2){
            qDebug() << "TextPropertyViewer2::keyPressEvent : F2 -> applyRequested";
                stopEdit();
                emit applyRequested();
        }
    } else {
        editor->startEdit();
        editing=true;
        e->ignore();
    }
}
// void TextPropertyEditorDialog::stopEdit()
// {
// 	if(editor){
// 		editor->stopEdit();
// 	}
// }

void TextPropertyViewer2::resizeEvent(QResizeEvent *e)
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

QSize TextPropertyViewer2::sizeHint()
{
    if(fit){
        return label->size();
    } else {
        return QWidget::sizeHint();
    }
}


 QString TextPropertyViewer2::getCompileStringVorn()
{
   qDebug() << "WARNING QString TextPropertyViewer::getCompileStringVorn() : do nothing";
   /*
     QString fileName = getTexFileName();

   QFile texFile(fileName);
    if(!texFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        return "Failed to open file";
    }
    QTextStream stream(&texFile);
    stream << header.arg(height).arg(width);

    if(prop && parent){
        stream << prop->asString(parent).c_str();
    } else {
        stream << displayString;
    }

    stream << footer;


    return fileName;
    */
}


/*
void TextPropertyViewer2::compileVorn(bool reload)
{


}
*/







