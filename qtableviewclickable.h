#ifndef QTABLEVIEWCLICKABLE_H
#define QTABLEVIEWCLICKABLE_H

/* Dependencies */
#include <QTableView>

class QTableViewClickable : public QTableView
{
    Q_OBJECT
public:
    explicit QTableViewClickable(QWidget *parent = 0);
    
signals:
    void rightClicked(QContextMenuEvent* event);
public slots:
    
protected :

    void contextMenuEvent(QContextMenuEvent* event);

    void handleRightClicked();

    void handleContextualMenuPlay();

    void handleContextualMenuRemove();
};

#endif // QTABLEVIEWCLICKABLE_H
