/**
 * @file qtableviewclickable.h
 * @brief QTableView extension with right click support
 * @author Fabien Batteix & Jordan Vertaure
 * @version 1.0
 *
 * @section intro_sec Introduction
 * This file contain all stuff required to instantiate QTableViewClickable object.\n
 * The QTableViewClickable object is an extension of the standard QTableView widget with right click support.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @section license_sec License
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * \n
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * \n
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */
#ifndef QTABLEVIEWCLICKABLE_H
#define QTABLEVIEWCLICKABLE_H

/* Dependencies */
#include <QTableView>

/* Forward declarations */
class QWidget;
class QContextMenuEvent;

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
