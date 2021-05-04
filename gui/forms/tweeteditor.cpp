#include "tweeteditor.h"
#include <QVBoxLayout>


TweetEditor::TweetEditor(QWidget *pw)
    : PObjectIconView(pw)
{

}

TweetEditor::TweetEditor(RepositoryProperty *prop, PObject *parentObject, QWidget *parent)
    : PObjectIconView(prop,parentObject,parent)
{

}

TweetEditor::TweetEditor(AbstractMapper *mapper, QWidget *parent)
    : PObjectIconView(mapper,parent)
{

}

PObjectIconViewItemBase* TweetEditor::doCreateItem(PObject *o)
{
    PObjectIconViewItemBase *item=0;

    if(o){
        //icon = GuiConfig::getInstance()->getIcon(o);
        if(displayPropList){
                item=new TweetEditorItem(
                            o,this,displayPropList->front());
        }
        addItem(item);
    }

    return item;
}



TweetEditorItem::TweetEditorItem(PObject *o, QListWidget *iv, RepositoryProperty *tP)
    : PObjectIconViewItemBase(o, iv)
{
    setSizeHint(QSize(0,200));
    iv->setItemWidget(this,new TweetEditorItemWidget(o,iv,tP));
}

TweetEditorItemWidget::TweetEditorItemWidget(PObject *o, QListWidget *iv, RepositoryProperty *tP)
    :QWidget(iv)
{
    textProp = tP;
    m_o=o;

    //dispWidget = new QWidget(iv);
    QVBoxLayout *l = new QVBoxLayout(this);

    titleLabel = new QLabel(o->getName().c_str(), this);
    textEdit = new QTextEdit(this);
    textEdit->setAutoFormatting(QTextEdit::AutoAll);
    //textEdit->setFixedHeight(200);
    textEdit->setMarkdown(textProp->asString(o).c_str());

    l->addWidget(titleLabel,1);
    l->addWidget(textEdit,10);




    connect(textEdit,SIGNAL(textChanged()),this,SLOT(readText()));

}

void TweetEditorItemWidget::readText()
{
    textProp->fromString(textEdit->toPlainText().toStdString(), m_o);
}

/*
void TweetEditorItemWidget::keyPressEvent(QKeyEvent *ev)
{
    qDebug() << " TweetEditorItemWidget::keyPressEvent";
}
*/

void TweetEditorItemWidget::leaveEvent(QEvent *ev)
{
    qDebug() << " TweetEditorItemWidget::leaveEvent";

    textEdit->setReadOnly(true);
    textEdit->document()->setModified(true);

}

void TweetEditorItemWidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
    qDebug() << " TweetEditorItemWidget::mouseDoubleClickEvent";
    textEdit->setReadOnly(false);

}
