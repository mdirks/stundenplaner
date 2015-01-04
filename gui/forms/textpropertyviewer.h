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
#include "kdialog.h"
#include "textpropertyeditor.h"

#include <QScrollArea>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QColor>

class TextPropertyLabel : public QScrollArea
{
Q_OBJECT

public:
	TextPropertyLabel(QWidget *parent=0, const char *name=0);
	
    void setText(QString s);
    void setPixmap(QPixmap pm);
    void emitEditRequested();


protected:
	void mouseDoubleClickEvent ( QMouseEvent * e );
	//void mousePressEvent ( QMouseEvent * e );
	//void keyPressEvent ( QKeyEvent * e );

signals:
	void editRequested();
    void labelClicked();

	//void switchRequested();
	//void nextRequested();
	
private:
	QLabel *label;

};


class TextPropertyViewer : public QWidget
{
Q_OBJECT

public:
    TextPropertyViewer(PObject *parent, RepositoryProperty *prop, QWidget *pw=0L, double w=18.0, double h=28.0);
    TextPropertyViewer(PObject *parent, QString displayString, QWidget *pw=0L);
	~TextPropertyViewer();

    void setParentObject(PObject *o);
    void setProperty(RepositoryProperty *p);

	QString getCompileStringVorn();
	void compileVorn(bool reload);
    void setHidden(bool h);
    void setFitToView(bool f);
    void setScrollBarPolicy(Qt::ScrollBarPolicy policy);

    void setFooter(QString f);
    void setHeader(QString f);
    void setBackgroundColor(QColor c);

    QSize sizeHint();

public slots:
	void editVorn();
	void readVorn();
	void stopEdit();
    void compileFinished(int code, QProcess::ExitStatus exitStatus);
    void compileError( QProcess::ProcessError error);

signals:
	void applyRequested();

protected:
	void keyPressEvent ( QKeyEvent * e );
    void resizeEvent ( QResizeEvent *e);

private:
    QString getFileName();
    void setDisplayPixmapToLabel(QPixmap dpm);


public:
    static QString StandardHeader, StandardFooter;


private:
	PObject *parent;
	RepositoryProperty *prop;
	QDir tmpDir;
	TextPropertyEditor *editor;
	TextPropertyLabel *label;
	QString displayString;
	bool editing;
    bool hidden;
    bool fit;
    QProcess *p;
    QString header,footer;
    QPixmap displayPm;
    QStackedWidget *stack;
       QSize displaySize;
       QColor bgColor;
     double width,height;
};
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class TextPropertyEditorDialog : public KDialog
{
Q_OBJECT

public:
        TextPropertyEditorDialog(PObject *parent, QString displayString, QWidget *pw=0L);

    TextPropertyEditorDialog(PObject *parent, RepositoryProperty *prop, QWidget *pw=0L);
    ~TextPropertyEditorDialog();

    static void edit(RepositoryProperty *prop, PObject *parent);
    static void display(QString displayString, PObject *parent);
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
	PObject *parent;
	RepositoryProperty *prop;
	QDir tmpDir;
*/
};

#endif
