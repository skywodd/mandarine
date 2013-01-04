/**
 * @file infoexplorer.h
 * @brief Wikipedia informations widget
 * @author Fabien Batteix & Jordan Vertaure
 * @version 1.0
 *
 * @section intro_sec Introduction
 * This file contain all stuff required to instantiate InfoExplorer object.\n
 * The InfoExplorer object is designed to display wikipedia informations about the specified terms.\n
 * Informations are displayed in WebKit as mobile view.\n
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
#ifndef INFOEXPLORER_H
#define INFOEXPLORER_H

/* Dependencies */
#include <QWidget>
#include "ui_infoexplorer.h"

/**
 * @brief Wikipedia display widget
 *
 * This widget is designed to display wikipedia informations about album or authors.
 */
class InfoExplorer : public QWidget, protected Ui::InfoExplorer
{
    Q_OBJECT
    
public:
    /**
     * Default constructor of the widget
     *
     * @brief InfoExplorer constructor
     * @param parent Parent widget
     */
    explicit InfoExplorer(QWidget *parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief InfoExplorer destructor
     * @remarks Ready for overload
     */
    virtual ~InfoExplorer();

    /**
     * Display available informations about the specified terms
     *
     * @brief showInformation
     * @param terms The terms to search on wikipedia and display
     */
    void showInformation(const QString& terms);
};

#endif // INFOEXPLORER_H
