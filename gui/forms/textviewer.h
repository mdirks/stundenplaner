#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include "gui/forms/pdfviewer.h"
#include "gui/forms/pobjectcombobox.h"
#include "datamodel/lektuere.h"
#include "pobjectlistprovider.h"
#include "gui/forms/collectiondisplay.h"
#include <QWidget>
#include <QToolBar>
#include <QResizeEvent>
#include <QSplitter>

#include <list>

class TextViewer;

class BookmarkActivationHandler : public PObjectIconViewActivationHandler
{
public:
    BookmarkActivationHandler(TextViewer *tw);
    void handleActivation(PObject *o);

private:
    TextViewer *m_textView;
};

class TextViewer : public QWidget
{
    Q_OBJECT
public:
    explicit TextViewer(QWidget *parent = 0);
    TextViewer(RepositoryProperty *rp,PObject *parent, QWidget *pw=0);
    TextViewer(PObjectListProvider *provider, QWidget *pw=0);
    
    void setPage(int i);
    int getPage();
    void load();
    void setResizePolicy(bool res);
    void setProvider(PObjectListProvider *prov);
    void addSelectionAction(PdfViewSelectionAction *a);
    void addKeyAction(Qt::Key key, PdfView::PdfViewAction a);
    void addContextMenuAction(PdfView::PdfViewAction a);
    CollectionDisplay* collectionDisplay(){return colDisplay;};

private:
    void doCommonSetup();
    //void setTextList(list<lektuere*> *tlist);
    void setParentObject(PObject *o);


signals:
    void textChanged(lektuere *l);
    
public slots:
    //void selectionChanged(int i);
    void showSelectionMenu();
    void loadNewLektuere();




private:
    PdfViewer *viewer;
    PObjectComboBox *combo;
    QToolBar *toolBar;
    list<lektuere*> *tlist;
    lektuere *activeText;
    PObjectListProvider *provider;

    QSplitter *splitter;
    CollectionDisplay *colDisplay;
    QToolButton *selectButton;
    QSplitter *colSplitter, *bookmarkSplitter;
    //PObjectIconView *bmView;
};

#endif // TEXTVIEWER_H
