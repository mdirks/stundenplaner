#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include "gui/forms/pdfviewer.h"
#include "gui/forms/pobjectcombobox.h"
#include "datamodel/lektuere.h"

#include <QWidget>
#include <QToolBar>
#include <QResizeEvent>

#include <list>

class TextViewer : public QWidget
{
    Q_OBJECT
public:
    explicit TextViewer(QWidget *parent = 0);
    TextViewer(RepositoryProperty *rp,PObject *parent, QWidget *pw=0);
    
    void setTextList(list<lektuere*> *tlist);
    void setPage(int i);
    void load();
    void setParentObject(PObject *o);

signals:
    void textChanged(lektuere *l);
    
public slots:
    void selectionChanged(int i);



private:
    PdfViewer *viewer;
    PObjectComboBox *combo;
    QToolBar *toolBar;
    list<lektuere*> *tlist;
    lektuere *activeText;
};

#endif // TEXTVIEWER_H
