/* Includes */
#include <QContextMenuEvent>
#include "qtreeviewclickable.h"

QTreeViewClickable::QTreeViewClickable(QWidget *parent) :
    QTreeView(parent)
{
}

QTreeViewClickable::~QTreeViewClickable()
{
}

void QTreeViewClickable::contextMenuEvent(QContextMenuEvent* event)
{
    /* Emit signal for rigth click */
    emit rightClicked(event);

    /* Resend event to parent */
    QTreeView::contextMenuEvent(event);
}
