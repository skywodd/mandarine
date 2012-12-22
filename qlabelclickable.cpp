/* Includes */
#include <QMouseEvent>
#include "qlabelclickable.h"

QLabelClickable::QLabelClickable(QWidget *parent) :
    QLabel(parent)
{
}

QLabelClickable::~QLabelClickable()
{
}

void QLabelClickable::mousePressEvent(QMouseEvent * event)
{
    /* Check if user has double clicked on the label */
    if(event->type() == QEvent::MouseButtonPress)
        /* If yes, emit clicked() signal */
        emit clicked();
}
