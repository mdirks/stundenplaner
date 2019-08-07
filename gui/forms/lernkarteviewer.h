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
#ifndef LERNKARTEVIEWER_H
#define LERNKARTEVIEWER_H

#include "datamodel/lernkarte.h"
#include "datamodel/lernkartensatz.h";
#include "pobjecticonview.h"
#include "textpropertyeditor.h"
#include "textpropertyviewer.h"
#include "pobjectcombobox.h"

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QDir>
//#include <ktrader.h>
//#include <klibloader.h>
#include <KParts/Part>
#include <KParts/ReadOnlyPart>

#include <list>
#include <QProcess>
#include <QStackedWidget>

using namespace std;
/**
	@author Marcus Dirks <m-dirks@web.de>
*/


class LernkarteViewer;

class LernkarteViewerEditor : public TextPropertyEditor
{
Q_OBJECT

public:
    LernkarteViewerEditor(LernkarteViewer *viewer, QWidget *parent=0);
    //void startEdit(lernkarte* lk, bool vorn);

public slots:
	void stopEdit();

private:
    //TextPropertyEditor *textEditorVorn, *textEditorHinten;
    //TextPropertyEditor *textEditor;
	lernkarte *lk;
	LernkarteViewer *viewer;
	bool vorn;

};







class LernkarteViewer : public QWidget
{
Q_OBJECT

public:
    enum Orientation{
        Horizontal=0,
        Vertical=1,
        Stacked=2
    };



public:
    LernkarteViewer(QWidget *parent=0,LernkarteViewer::Orientation=LernkarteViewer::Horizontal);
    ~LernkarteViewer();

    void setLernkarte(lernkarte *lk);
    //void setLernkartensatz(lernkartensatz *ls);
    //void compileVorn(lernkarte *lk, bool reload=false);
    //void compileHinten(lernkarte *lk, bool reload=false);

    QSize sizeHint();

public:
    static QString header, footer;

//protected:
//	void keyPressEvent ( QKeyEvent * e );
protected:
    void keyPressEvent ( QKeyEvent * e );
    void mousePressEvent(QMouseEvent *e);
private:


signals:
    void nextRequested();

public slots:
    //void setSelected(int i);
    //void showCurrent();
    //void advance();
    void switchDisplay();
    void showHinten();
    void showVorn();
    void switchHinten();
    //void showEditor(bool vorn);
    void showLabels();

private:
    lernkarte* active_lk;
    KParts::ReadOnlyPart *pdf_part;

    TextPropertyViewer *viewerVorn, *viewerHinten;
    //LernkarteViewerLabel *label_vorn, *label_hinten;
    //LernkarteViewerEditor *editor_vorn, *editor_hinten;
    //PObjectComboBox *combo;
    //lernkartensatz *ls;
    list<lernkarte*> *list_karten;
    list<lernkarte*>::iterator it_ak;
    bool showsVorn, showsHinten;
    QDir tmpDir;
     QProcess *pvorn, *phinten;
     QStackedWidget *stack;
     QWidget *blankWidget;
    // int currentIndex;
    LernkarteViewer::Orientation orientation;

};


class LernkartensatzViewer : public QWidget
{
Q_OBJECT

public:
    LernkartensatzViewer(lernkartensatz* ls, QWidget *parent=0,LernkarteViewer::Orientation=LernkarteViewer::Horizontal);
    ~LernkartensatzViewer();

    void setLernkartensatz(lernkartensatz *ls);
    QSize sizeHint();


public slots:
    void setSelected(int i);
    void advance();

private:
    LernkarteViewer *karteViewer;
    PObjectComboBox *combo;
    lernkartensatz *ls;
    int currentIndex;
};

#endif
