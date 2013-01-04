#ifndef QTABLEVIEWCLICKABLE_H
#define QTABLEVIEWCLICKABLE_H

/* Dependencies */
#include <QTableView>

/**
 * @brief QTableView with rigth click support
 *
 * This class is a enhanced version of QTableView widget with rigth click support
 */
class QTableViewClickable : public QTableView
{
    Q_OBJECT

public:
    /**
     * Default constructor of the widget
     *
     * @brief QTableViewClickable constructor
     * @param parent Parent widget
     */
    explicit QTableViewClickable(QWidget* parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief QTableViewClickable destructor
     * @remarks Ready for overload
     */
    virtual ~QTableViewClickable();
    
signals:
    /**
     * Signal emitted when user rigth click in the widget
     *
     * @brief rightClicked
     * @param event Requested QContextMenuEvent event
     */
    void rightClicked(QContextMenuEvent* event);

protected:
    /**
     * Overload of the default QTableView contextMenuEvent() for rigth click support
     *
     * @brief contextMenuEvent
     * @param event Requested QContextMenuEvent event
     */
    void contextMenuEvent(QContextMenuEvent* event);
};

#endif // QTABLEVIEWCLICKABLE_H
