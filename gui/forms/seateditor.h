//
// C++ Interface: seateditor
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SEATEDITOR_H
#define SEATEDITOR_H

#include "datamodel/schueler.h"
#include "datamodel/platz.h"
#include "datamodel/klasse.h"
#include "datamodel/stundenplaneintrag.h"
#include "pobjectlabel.h"
#include "gui/base/editrequestor.h"

#include <qwidget.h>
#include <qlineedit.h>
#include <QTableWidget>

#include <list>
#include <map>

using namespace std;

class NameWidget;
class MarkWidget;
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class SeatEditor : public QWidget {

Q_OBJECT

public:
    SeatEditor(platz *p, klasse *kl, map<int, list<stundenplaneintrag*>* > map_eintraeg, QWidget *parent=0);
    ~SeatEditor();

    //void setSchueler(schueler *s);

public slots:
	void loadEintraege();

public:
	EditRequestor *editRequestor;
	schueler* getSchueler();

private:
	//schueler *m_s;
	platz *pl;
	klasse *kl;
	PObjectLabel *nameWidget;
    QTableWidget *stundenTable;
	map<int,list<stundenplaneintrag*>* > map_eintraege;
	//NameWidget *nameWidget;
};


class NameWidget : public QWidget {

Q_OBJECT

public:
	NameWidget(QWidget *parent=0);
	~NameWidget();

	void setSchueler(schueler *s);

private:
	QLineEdit *nameEdit, *tutorEdit;


};

class MarkWidget : public QWidget /*QPushButton*/ {


Q_OBJECT

public: 
	MarkWidget(schueler *s, note *n, QWidget *parent, SeatEditor *editor);
	MarkWidget(schueler *s, stundenplaneintrag *e, QWidget *parent, SeatEditor *editor);
	~MarkWidget();

	void setMark(QString m);

public slots:
	void editNote();
	void setFehlzeit();

private:
	note *n;
	schueler *s;
	stundenplaneintrag *e;
	stundenbewertung *bew;
	QPushButton *bedit, *bfehl;
	
	SeatEditor *seatEditor;


	
};

#endif
