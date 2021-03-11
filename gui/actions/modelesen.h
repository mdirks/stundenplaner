#ifndef MODELESEN_H
#define MODELESEN_H

#include "datamodel/notizholder.h"
#include "datamodel/lektuere.h"
#include "gui/guimode.h"
#include "gui/forms/textpropertybrowser.h"
#include "gui/forms/textviewer.h"
#include "gui/forms/lernkarteviewer.h"
#include "gui/forms/pobjectdisplay.h"
#include "gui/forms/tweeteditor.h"
#include <list>
#include <QSplitter>
#include <QToolBar>
#include <QStackedWidget>

class ModeLesen : public GuiMode //, public notizholder
{
   Q_OBJECT
friend class AddBookmarkAction;

public:
    ModeLesen();

    void setupMode();
    void tearDownMode();
    void close();
    void load();

    void activateObject(PObject *o);
    void showForm(QWidget *w);

    /*
    list<lektuere*> *getTexte();
    void addToTexte(lektuere *l);
    void deleteFromTexte(lektuere *l);
    */

    lektuere* getActiveText();
    //static ModeLesen* getInstance();

    void setActivePage(int i);

private:
    void doCommonSetup();

public slots:
    void showNotizeditor();
    void showLernkarten();
    void showLernkartenDisplay();
    void showMaterialDisplay();
    void setActiveText(lektuere *l);
    void takeNote(QString note);
    void takeCopy(QImage i);
    void addBookmark(double pos);
    void showBookmarks();
    void showTweets();

private:
    static ModeLesen *instance;
    TextViewer *viewer;
    TextPropertyBrowser *browser;
    LernkartensatzViewer *lkViewer;
    PObjectDisplay *lkDisplay;
    PObjectDisplay *mDisplay;
    PObjectIconView *bmView;
    TweetEditor *tweetEdit;

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


class TakeNoteAction : public PdfViewSelectionAction
{
    Q_OBJECT

public:
    TakeNoteAction(ModeLesen *parent);
    void setDataText(QString t);

public slots:
    void createLektuereNotiz();


private:
    ModeLesen *mode;
};


class TakeCopyAction : public PdfViewSelectionAction
{
    Q_OBJECT

public:
    TakeCopyAction(ModeLesen *parent);
    void setDataImage(QImage i);

public slots:
    void createLektuereCopy();


private:
    ModeLesen *mode;
};

class AddBookmarkAction : public PdfViewSelectionAction
{
    Q_OBJECT
//friend class PdfView;

public:
    AddBookmarkAction(ModeLesen *parent);
    //void setDataImage(QImage i);
    //void setPosition(double pos);

public slots:
    void addBookmark();


private:
    ModeLesen *mode;
};

class LektuereDropHandler : public PObjectIconViewDropHandler
{
public:
    bool canHandle(QDragEnterEvent *e);
    bool canHandle(QDragMoveEvent *e);
    bool dropEvent(QDropEvent *e);


};


#endif // MODELESEN_H
