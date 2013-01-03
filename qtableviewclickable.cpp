#include <QDebug>
#include <QMenu>
#include <QModelIndex>
#include <QContextMenuEvent>

#include "qtableviewclickable.h"

QTableViewClickable::QTableViewClickable(QWidget *parent) :
    QTableView(parent)
{

}



void QTableViewClickable::contextMenuEvent(QContextMenuEvent* event)
{

        emit rightClicked(event);
}


