#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include "pdfview.h"
#include <QSize>

class PdfViewer : public PdfView
{
public:
    PdfViewer(QWidget *parent=0);

    void loadNewFile(QString fileName);

protected:
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dropEvent(QDropEvent *e);
    virtual void dragMoveEvent(QDragMoveEvent* e);

    virtual void resizeEvent(QResizeEvent *event);

private:
    QSize psize;
};

#endif // PDFVIEWER_H
