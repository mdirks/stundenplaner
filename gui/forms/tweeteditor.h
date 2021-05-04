#ifndef TWEETEDITOR_H
#define TWEETEDITOR_H

#include "pobjecticonview.h"

class TweetEditor : public PObjectIconView
{
public:
    TweetEditor(QWidget *parent=0);
    TweetEditor(RepositoryProperty *prop, PObject *parentObject, QWidget *parent=0);
    TweetEditor(AbstractMapper *mapper, QWidget *parent=0);
protected:
    PObjectIconViewItemBase* doCreateItem(PObject *o);
};


class TweetEditorItem : public PObjectIconViewItemBase
{

public:
    TweetEditorItem(PObject *o, QListWidget *iv, RepositoryProperty *textProp);

};

class TweetEditorItemWidget : public QWidget
{
    Q_OBJECT

public:
    TweetEditorItemWidget(PObject *o, QListWidget *iv, RepositoryProperty *textProp);

public slots:
    void readText();

protected:
    //void keyPressEvent(QKeyEvent *ev);
    void leaveEvent(QEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *ev);

private:
    //QWidget *dispWidget;
    QTextEdit *textEdit;
    QLabel *titleLabel;
    RepositoryProperty *textProp;
    PObject *m_o;
};


#endif // TWEETEDITOR_H
