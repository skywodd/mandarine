/**
 * @file qlabelclickable.h
 * @brief QLabel with click support
 * @author Fabien Batteix & Jordan Vertaure
 * @version 1.0
 *
 * @section intro_sec Introduction
 * This file contain all stuff required to instantiate QLabelClickable object.\n
 * The QLabelClickable object is a extension of the standard QLabel widget with click support.\n
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
#ifndef QLABELCLICKABLE_H
#define QLABELCLICKABLE_H

/* Dependencies */
#include <QLabel>

/* Forward declarations */
class QWidget;
class QMouseEvent;

/**
 * @brief Clickable label widget
 *
 * This class is a extension of the classical QLabel widget with clicked() signal support.
 */
class QLabelClickable : public QLabel
{
    Q_OBJECT

public:
    /**
     * Default constructor of the widget
     *
     * @brief QLabelClickable constructor
     * @param parent Parent widget
     */
    explicit QLabelClickable(QWidget *parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief QLabelClickable destructor
     */
    virtual ~QLabelClickable();

protected:
    /**
     * "Mouse Press Event" handler
     *
     * @brief mousePressEvent overload
     * @param event Received mouse event
     */
    virtual void mousePressEvent(QMouseEvent* event);

signals:
    /**
     * Clicked signal
     *
     * @brief clicked
     */
    void clicked();
};

#endif // QLABELCLICKABLE_H
