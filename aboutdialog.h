/**
 * @file aboutdialog.h
 * @brief About dialog class
 * @author Fabien Batteix & Jordan Vertaure
 * @version 1.0
 *
 * @section intro_sec Introduction
 * This file contain all stuff required for instanciate AboutDialog object.\n
 * The AboutDialog object is a dialog box with informations about the program.\n
 * Informations like program version, authors and more are provided.\n
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
#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

/* Dependencies */
#include <QDialog>
#include "ui_aboutdialog.h"

/* Forward declarations */
class QWidget;

/**
 * @brief About dialog
 *
 * This class is designed as a QDialog extension for displaying about informations.
 */
class AboutDialog : public QDialog, protected Ui::AboutDialog
{
    Q_OBJECT

public:
    /**
     * Default constructor of the dialog
     *
     * @brief AboutDialog constructor
     * @param parent Parent widget
     */
    explicit AboutDialog(QWidget* parent = 0);

    /**
     * Default destructor of the dialog
     *
     * @brief AboutDialog destructor
     * @remarks Ready for overload
     */
    virtual ~AboutDialog();
};

#endif // ABOUTDIALOG_H
