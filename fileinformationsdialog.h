/**
 * @file fileinformationsdialog.h
 * @brief Audio file's informations dialog box
 * @author Fabien Batteix & Jordan Vertaure
 * @version 1.0
 *
 * @section intro_sec Introduction
 * This file contain all stuff required to instanciate FileInformationsDialog object.\n
 * The FileInformationsDialog object is a dialog box with informations about audio file's properties.\n
 * Informations like path, bitrate, codec, size are provided.\n
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
#ifndef FILEINFORMATIONSDIALOG_H
#define FILEINFORMATIONSDIALOG_H

/* Dependencies */
#include <QDialog>
#include "ui_fileinformationsdialog.h"

/* Forward declarations */
class QWidget;
class QMediaResource;

/**
 * @brief Audio file's informations dialog
 *
 * This class is designed as a QDialog extension for displaying audio file's properties.
 */
class FileInformationsDialog : public QDialog, protected Ui::FileInformationsDialog
{
    Q_OBJECT
    
public:
    /**
     * Default constructor of the dialog
     *
     * @brief FileInformationsDialog constructor
     * @param parent Parent widget
     */
    explicit FileInformationsDialog(QWidget* parent = 0);

    /**
     * Default destructor of the dialog
     *
     * @brief FileInformationsDialog destructor
     * @remarks Ready for overload
     */
    virtual ~FileInformationsDialog();

public slots:
    /**
     * Display informations about the specified QMediaResource object
     *
     * @brief displayInfo
     * @param source Source QMediaResource pointer to display
     */
    void displayInfo(const QMediaResource* source);
};

#endif // FILEINFORMATIONSDIALOG_H
