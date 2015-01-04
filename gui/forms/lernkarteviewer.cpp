/***************************************************************************
 *   Copyright (C) 2008 by Marcus Dirks   *
 *   m-dirks@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "lernkarteviewer.h"
#include "gui/guirepository.h"
#include "qlayout.h"
#include "qimage.h"
#include "qlabel.h"
#include "qprocess.h"
#include "gui/actions/datenpopup.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"
#include <ktrader.h>
#include <klibloader.h>
#include <kprocess.h>
#include <krun.h>
#include <poppler-qt4.h>
#include <QDebug>
#include <QMouseEvent>
#include <QSplitter>
#include <QToolBar>

#include <algorithm>
#include <functional>

QString LernkarteViewer::header = "\\documentclass[11pt]{extarticle}\\usepackage[paperheight=100mm,paperwidth=50mm,landscape]{geometry}\\pagestyle{empty}\\oddsidemargin=-22mm\\textwidth=98mm\\begin{document}\\sffamily\\vspace*{\\fill}";
QString LernkarteViewer::footer = "\\vspace*{2cm}\\mbox{}\\vspace*{\\fill}\\end{document}";


LernkartensatzViewer::LernkartensatzViewer(lernkartensatz *ls, QWidget *parent, LernkarteViewer::Orientation ori)
    : QWidget(parent),ls(ls)
{
    RepositoryProperty *rp=Repository::getInstance()->getRepositoryEntry("lernkartensatz")->getProperty("Lernkarten");
    this->combo = new PObjectComboBox(rp,ls,this);
    connect(combo,SIGNAL(currentIndexChanged(int)),this,SLOT(setSelected(int)));

    this->karteViewer = new LernkarteViewer(parent,ori);
    connect(karteViewer,SIGNAL(nextRequested()),this,SLOT(advance()));

    QVBoxLayout *topLayout = new QVBoxLayout(this);
    QToolBar *toolBar = new QToolBar(this);
    toolBar->addWidget(combo);
    topLayout->addWidget(toolBar);
    topLayout->addWidget(karteViewer);
}

LernkarteViewer::LernkarteViewer(QWidget *parent, LernkarteViewer::Orientation ori)
 : tmpDir(QDir::current().path() + QDir::separator() + "tmp"),  orientation(ori), QWidget(parent)
{
	pdf_part=0;
    list_karten=0;
    active_lk=0;


    RepositoryProperty *rp= 0;
    rp=Repository::getInstance()->getRepositoryEntry("lernkarte")->getProperty("SourceVorn");
    viewerVorn = new TextPropertyViewer(0,rp,this);
    //viewerVorn->setFitToView(true);
    viewerVorn->setScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewerVorn->setMinimumSize(300,200);
    viewerVorn->setHeader(header);
    viewerVorn->setFooter(footer);
    viewerVorn->setBackgroundColor(QColor(255, 255, 255, 127));
    rp= Repository::getInstance()->getRepositoryEntry("lernkarte")->getProperty("SourceHinten");
    viewerHinten= new TextPropertyViewer(0,rp,this);
    //viewerHinten->setFitToView(true);
    viewerHinten->setScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewerHinten->setHeader(header);
    viewerHinten->setFooter(footer);
    viewerHinten->setBackgroundColor(QColor(255, 0, 0, 27));


    /*
    rp=Repository::getInstance()->getRepositoryEntry("lernkartensatz")->getProperty("Lernkarten");
    combo = new PObjectComboBox(rp,ls,this);
    connect(combo,SIGNAL(currentIndexChanged(int)),this,SLOT(setSelected(int)));
    */

    QVBoxLayout *topLayout = new QVBoxLayout();
    topLayout->setContentsMargins(0,0,0,0);
    topLayout->setSpacing(0);
    //QToolBar *toolBar = new QToolBar(this);
    //toolBar->addWidget(combo);
    //topLayout->addWidget(toolBar);


    if(ori==Horizontal){
        QWidget *displayWidget = new QWidget(this);
        QGridLayout *gl = new QGridLayout(displayWidget);

        gl->addWidget(viewerVorn,0,0);
        gl->addWidget(viewerHinten,0,1);

        topLayout->addWidget(displayWidget,10);
        topLayout->setSpacing(0);
        displayWidget->show();
    } else if(ori==Vertical){
        QWidget *displayWidget = new QWidget(this);
        QGridLayout *gl = new QGridLayout(displayWidget);

        gl->addWidget(new QLabel("1"),0,0);
        //gl->addWidget(toolBar,1,1);
        gl->addWidget(viewerVorn,1,2);
        gl->addWidget(viewerHinten,1,3);
        gl->addWidget(new QLabel("2"),0,1);
        gl->setColumnStretch(0,10);
        gl->setRowStretch(0,10);

        topLayout->addWidget(displayWidget,10);
        topLayout->setSpacing(0);
        displayWidget->show();
    } else if(ori==Stacked){
        stack=new QStackedWidget(this);
        //stack->setContentsMargins(0,0,0,0);
        stack->setStyleSheet("background-color:white;");
        viewerVorn->setParent(stack);
        viewerVorn->setMinimumSize(100,100);
        stack->addWidget(viewerVorn);
        viewerHinten->setParent(stack);
        stack->addWidget(viewerHinten);

        /*
        gl->addWidget(new QLabel("1",displayWidget),0,0,2,1);
        gl->addWidget(stack,1,0);
        gl->addWidget(new QLabel("2",displayWidget),1,1);
        gl->setColumnStretch(0,10);
        gl->setRowStretch(0,10);
        */

        //gl->addWidget(stack);

        topLayout->addWidget(stack);
        this->setStyleSheet("background-color:red;");
        this->setContentsMargins(0,0,0,0);
        this->setLayout(topLayout);
        //topLayout->addWidget(displayWidget);
        //setSizePolicy(viewerVorn->sizePolicy());
    }




    showVorn();


}

QSize LernkartensatzViewer::sizeHint()
{
    return karteViewer->sizeHint();
}

QSize LernkarteViewer::sizeHint()
{
    if(orientation==LernkarteViewer::Stacked){
        return viewerVorn->sizeHint();
    } else {
       return QWidget::sizeHint();
    }

}

void LernkarteViewer::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton){
        if(showsVorn){
            showHinten();
        } else {
            showVorn();
        }
    }

}

void LernkartensatzViewer::setSelected(int i)
{
    PObject *o = combo->getObject(i);
    if(lernkarte *lk=dynamic_cast<lernkarte*>(o)){
        //it_ak=std::find(list_karten->begin(),list_karten->end(),lk);
        karteViewer->setLernkarte(lk);
    }
}

LernkarteViewer::~LernkarteViewer()
{
}

LernkartensatzViewer::~LernkartensatzViewer()
{
}

void LernkartensatzViewer::setLernkartensatz(lernkartensatz *ls)
{
	this->ls = ls;
    if(ls){
        combo->setParentObject(ls);
    }
}

/*
void LernkarteViewer::showCurrent()
{
	PObject *o=listView->getSelected();
	lernkarte *lk = dynamic_cast<lernkarte*>(o);
	if(lk){
        setLernkarte(lk);
	} else {
		qDebug("LernkarteViewer::showCurrent : Could not selected Lernkarte");
	}
}
*/

void LernkarteViewer::setLernkarte(lernkarte *lk)
{
	
	if(lk){
		active_lk = lk;
        viewerVorn->setParentObject(lk);
        viewerHinten->setParentObject(lk);
        //it_ak=find(list_karten->begin(),list_karten->end(),active_lk);
	}
}




void LernkarteViewer::showVorn()
{
    if(orientation==Stacked){
        stack->setCurrentWidget(viewerVorn);
    }
    viewerHinten->stopEdit();
    viewerHinten->setHidden(true);
    viewerHinten->readVorn();
    viewerVorn->setHidden(false);
    viewerVorn->readVorn();
    viewerVorn->setFocus();

	showsVorn=true;
}

void LernkarteViewer::showHinten()
{
    if(orientation==Stacked){
        stack->setCurrentWidget(viewerHinten);
    }
    viewerVorn->stopEdit();
    viewerVorn->setHidden(true);
    viewerVorn->readVorn();
    viewerHinten->setHidden(false);
    viewerHinten->readVorn();
    viewerHinten->setFocus();
	showsVorn=false;
}

void LernkarteViewer::switchDisplay()
{
	if(showsVorn){
		showHinten();
	} else {
		showVorn();
	}
}

void LernkarteViewer::showLabels()
{
	if(showsVorn){
		showVorn();
	} else {
		showHinten();
	}
}



void LernkartensatzViewer::advance()
{
    int i=combo->currentIndex()+1;
    if(i>=(combo->model()->rowCount()-1)) i=0;
    combo->setCurrentIndex(i);
	
}





void LernkarteViewer::keyPressEvent ( QKeyEvent * e )
{
	qDebug("LernkarteViewer::keyPressEvent ");
    if(e->key() == Qt::Key_Space || e->key() == Qt::Key_Down){
        showVorn();
        emit nextRequested();
    } else if(e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Right || e->key() == Qt::Key_Left){
		switchDisplay();
    } else  {
		e->ignore();
    }
}

LernkarteViewerEditor::LernkarteViewerEditor(LernkarteViewer *vw, QWidget *parent)
    : viewer(vw), TextPropertyEditor(parent)
{
    //connect(buttonOk, SIGNAL(clicked()), this, SLOT(stopEdit()));
}

/*
void LernkarteViewerEditor::startEdit(lernkarte *lk, bool vorn)
{
	this->lk = lk;
	this->vorn = vorn;
	RepositoryProperty *rp= Repository::getInstance()->getRepositoryEntry("lernkarte")->getProperty("SourceVorn");
	textEditorVorn->startEdit(rp,lk);
	rp = Repository::getInstance()->getRepositoryEntry("lernkarte")->getProperty("SourceHinten");
	textEditorHinten->startEdit(rp,lk);
	
	
}
*/

void LernkarteViewerEditor::stopEdit()
{
    TextPropertyEditor::stopEdit();
    //viewer->compileVorn(this->lk,true);
    //viewer->compileHinten(this->lk,true);
	viewer->showLabels();
	
}
