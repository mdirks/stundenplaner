#ifndef MODELESEN_H
#define MODELESEN_H

#include "datamodel/notizholder.h"
#include "datamodel/lektuere.h"
#include "gui/guimode.h"
#include "gui/forms/textpropertybrowser.h"
#include "gui/forms/textviewer.h"
#include "gui/forms/lernkarteviewer.h"

#include <list>
#include <QSplitter>
#include <QToolBar>
#include <QStackedWidget>

class ModeLesen : public GuiMode, public notizholder
{
   Q_OBJECT

public:
    ModeLesen();

    void setupMode();
    void tearDownMode();

    void activateObject(PObject *o);
    void showForm(QWidget *w);

    list<lektuere*> *getTexte();
    void addToTexte(lektuere *l);
    void deleteFromTexte(lektuere *l);

    void setActiveText(lektuere *l);
    static ModeLesen* getInstance();

    void setActivePage(int i);

public slots:
    void showNotizeditor();
    void showLernkarten();

private:
    static ModeLesen *instance;
    TextViewer *viewer;
    TextPropertyBrowser *browser;
    LernkartensatzViewer *lkViewer;

    list<lektuere*> *list_texte;
    lektuere *activeText;

    QStackedWidget *stack;
    QWidget *blankWidget;
    QSplitter *splitter;
    QToolBar *toolBar;
};

class AdaptingSplitter : public QSplitter
{
public:
    AdaptingSplitter(QWidget *widget1, QWidget *widget2, QWidget *parent);

protected:
    void resizeEvent(QResizeEvent *);

private:
    QWidget *widget1, *widget2;

};

#endif // MODELESEN_H
