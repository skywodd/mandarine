#ifndef QTREEVIEWCLICKABLE_H
#define QTREEVIEWCLICKABLE_H

/* Dependencies */
#include <QTreeView>

/**
 * @brief QTreeView with rigth click support
 *
 * This class is a enhanced version of QTreeView widget with rigth click support
 */
class QTreeViewClickable : public QTreeView
{
    Q_OBJECT

public:
    /**
     * Default constructor of the widget
     *
     * @brief QTreeViewClickable constructor
     * @param parent Parent widget
     */
    explicit QTreeViewClickable(QWidget* parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief QTreeViewClickable destructor
     * @remarks Ready for overload
     */
    virtual ~QTreeViewClickable();

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
     * Overload of the default QTreeView contextMenuEvent() for rigth click support
     *
     * @brief contextMenuEvent
     * @param event Requested QContextMenuEvent event
     */
    void contextMenuEvent(QContextMenuEvent* event);
};

#endif // QTREEVIEWCLICKABLE_H
