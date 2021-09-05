//
// C++ Interface: textpropertyeditordialog
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef TEXTPROPERTYEDITORDIALOG_H
#define TEXTPROPERTYEDITORDIALOG_H
#include "qlabel.h"
#include "qdir.h"
#include "qimage.h"
#include "qprocess.h"
#include "qlabel.h"
#include <QDialog>
#include "textpropertyeditor.h"
#include "pdfviewer.h"

#include <QScrollArea>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QColor>

class TextPropertyLabel : public QWidget
{
Q_OBJECT

public:
    TextPropertyLabel(QWidget *parent=0, const char *name=0);
    TextPropertyLabel(PObject *o, RepositoryProperty *prop, QWidget *parent=0, const char *name=0);


    virtual void compileVorn(bool reload)=0;

public slots:
    virtual void read()=0;


public:
    //void setText(QString s);
    //void setPixmap(QPixmap pm);
    void emitEditRequested();
    void setParentObject(PObject *o){po=o;};
    void setProperty(RepositoryProperty *p){prop=p;};

    void setFooter(QString f);
    void setHeader(QString f);

protected:
    void mouseDoubleClickEvent ( QMouseEvent * e );
    //void mousePressEvent ( QMouseEvent * e );
    void keyPressEvent ( QKeyEvent * e );


    void compileFinished(int code, QProcess::ExitStatus exitStatus);
    void compileError( QProcess::ProcessError error);

signals:
    void editRequested();
    void labelClicked();

    //void switchRequested();
    //void nextRequested();

protected:
    //QLabel *label;
    PObject *po;
    RepositoryProperty *prop;
    QString header,footer;

};


class TextPropertyLabel_md : public TextPropertyLabel
{
    Q_OBJECT

public:
    TextPropertyLabel_md(QWidget *p=0, const char *name=0);
    TextPropertyLabel_md(PObject *o, RepositoryProperty *prop, QWidget *p=0, const char *name=0);

    void compileVorn(bool reload);

public slots:
    void read();

private:
    //QTextEdit *m_viewer;
    QLabel *m_viewer;
};

class TextPropertyLabel_pdf : public TextPropertyLabel
{
    Q_OBJECT
public:
    TextPropertyLabel_pdf(QWidget *p=0, const char *name=0);
    TextPropertyLabel_pdf(PObject *o, RepositoryProperty *prop, QWidget *p=0, const char *name=0);

    void compileVorn(bool reload);



    QString getCompileStringVorn();

public slots:
    void read();

public:
    static QString StandardHeader, StandardFooter;

private:
    QString getFileName();
    QString getTexFileName();

private:

    QDir tmpDir;
    PdfViewer *m_viewer;
    double twidth,theight;
    QString displayString;
    QProcess *p;


};





class TextPropertyViewer : public QWidget
{
Q_OBJECT

public:
    enum Type {PdfLabel, MdLabel};

public:
    TextPropertyViewer(QWidget *pw=0L, TextPropertyViewer::Type = PdfLabel);
    TextPropertyViewer(PObject *po, RepositoryProperty *prop, QWidget *pw=0L, double w=18.0, double h=28.0, TextPropertyViewer::Type = PdfLabel);
    //TextPropertyViewer(PObject *po, QString displayString, QWidget *pw=0L);
	~TextPropertyViewer();

    void setParentObject(PObject *o);
    void setProperty(RepositoryProperty *p);

    //QString getCompileStringVorn();
    //void compileVorn(bool reload);
    void setHidden(bool h);
    void setFitToView(bool f);
    void setScrollBarPolicy(Qt::ScrollBarPolicy policy);

    void setFooter(QString f){label->setFooter(f);};
    void setHeader(QString f){label->setFooter(f);};
    //void setBackgroundColor(QColor c);
    //void setZoomFactor(double f);
    //void setResizePolicy(bool res);

    QSize sizeHint();

public slots:
	void editVorn();
    //void readVorn();
	void stopEdit();
    //void compileFinished(int code, QProcess::ExitStatus exitStatus);
    //void compileError( QProcess::ProcessError error);

    void print();

signals:
	void applyRequested();

protected:
	void keyPressEvent ( QKeyEvent * e );
    void resizeEvent ( QResizeEvent *e);
    void contextMenuEvent(QContextMenuEvent *e);

private:
    //QString getFileName();
    //QString getTexFileName();
    //void setDisplayPixmapToLabel(QPixmap dpm);
    void doCommonSetup(TextPropertyViewer::Type t);






private:
    PObject *po;
	RepositoryProperty *prop;
    TextPropertyEditor *editor;
    TextPropertyLabel *label;
    //PdfViewer *label;
    bool editing;
    bool hidden;
    bool fit;


    QPixmap displayPm;
    QStackedWidget *stack;
       QSize displaySize;
    //   QColor bgColor;

};
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class TextPropertyEditorDialog : public QDialog
{
Q_OBJECT

public:
       // TextPropertyEditorDialog(PObject *parent, QString displayString, QWidget *pw=0L);

    TextPropertyEditorDialog(PObject *po, RepositoryProperty *prop, QWidget *pw=0L);
    ~TextPropertyEditorDialog();

    static void edit(RepositoryProperty *prop, PObject *po);
    //static void display(QString displayString, PObject *po);
    //QString getCompileStringVorn();
	//void compileVorn(bool reload);


public slots:
	//void editVorn();
	//void readVorn();
	void stopEdit();
	//void compileFinished();

// private:
// 	void stopEdit();

signals:
	void applyRequested();

protected:
	//void keyPressEvent ( QKeyEvent * e );


private:
	//TextPropertyEditor *editor;
	//TextPropertyLabel *label;
	TextPropertyViewer *viewer;
	QLabel *title;

/*
    PObject *po;
	RepositoryProperty *prop;
	QDir tmpDir;
*/
};

#endif
