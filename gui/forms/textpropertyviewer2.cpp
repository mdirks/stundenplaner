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

    doCommonSetup();

}

TextPropertyViewer2::TextPropertyViewer2(PObject *parent, RepositoryProperty *prop, QWidget *pw, double w, double h) :
    QWidget(pw), header(StandardHeader), footer(StandardFooter),
    tmpDir(QDir::current().path() + QDir::separator() + "tmp"),bgColor(Qt::lightGray),width(w), height(h)
{
    this->parent = parent;
    this->prop = prop;
    displayString=QString("Shouldnt be used");


    doCommonSetup();

}

void TextPropertyViewer2::doCommonSetup()
{


    label = new QLabel(this);
    label->setFrameStyle(QFrame::NoFrame);

    if(prop){
        editor = new TextPropertyEditor(parent,prop,this);
    } else {
        editor = new TextPropertyEditor(this);
    }
    editor->setFrameStyle(QFrame::NoFrame);
    label->setMinimumHeight(10);
    hidden=false;
    fit=false;

    splitter = new QSplitter(this);
    splitter->addWidget(editor);
    splitter->addWidget(label);
    /*
    stack= new QStackedWidget(this);
    stack->setFrameStyle(QFrame::NoFrame);
    stack->setContentsMargins(0,0,0,0);
    */

    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    l->setSpacing(0);
    l->addWidget(splitter);
    /*
    l->addWidget(stack);
    stack->addWidget(label);
    stack->addWidget(editor);
    */


    input.mathmode = "\\[ ... \\]";
    input.dpi = 150;
    input.preamble = QString("\\usepackage{amssymb,amsmath,mathrsfs}");

    if(!KLFBackend::detectSettings(&settings)) {
        qDebug() << "unable to find LaTeX in default directories.";
    } else {
        qDebug() << "default settings working!";
    }

    mPreviewBuilderThread = new KLFPreviewBuilderThread(this, input, settings);

    connect(editor, SIGNAL(textChanged()), this,
        SLOT(updatePreviewBuilderThreadInput()), Qt::QueuedConnection);
    connect(mPreviewBuilderThread, SIGNAL(previewAvailable(const QImage&, bool)),
        this, SLOT(showRealTimePreview(const QImage&, bool)), Qt::QueuedConnection);
    //connect(ui->clipBtn, SIGNAL(clicked()), this, SLOT(copyToClipboard()));

}

void TextPropertyViewer2::updatePreview()
{
    // in linux, I need to reinstate the preamble when rendering. No idea why.
    input.preamble = QString("\\usepackage{amssymb,amsmath}");
    input.latex = editor->toPlainText();
    if(mPreviewBuilderThread->inputChanged(input)) {
        qDebug() << "input changed. Render...";
        //ui->statusBar->showMessage("Input changed. Render...");
        mPreviewBuilderThread->start();
  }
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
