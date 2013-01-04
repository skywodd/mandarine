/* Includes */
#include <QContextMenuEvent>
#include "qtableviewclickable.h"

QTableViewClickable::QTableViewClickable(QWidget *parent) :
    QTableView(parent)
{
}

QTableViewClickable::~QTableViewClickable()
{
}

void QTableViewClickable::contextMenuEvent(QContextMenuEvent* event)
{
    /* Emit signal for rigth click */
    emit rightClicked(event);

    /* Resend event to parent */
    QTableView::contextMenuEvent(event);
}


