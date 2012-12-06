/**
 * @file audioformats.h
 * @brief The supported audio formats dialog
 * @author SkyWodd & jordanVertaure
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * TODO\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @section licence_sec Licence
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

#ifndef AUDIOFORMATSDIALOG_H
#define AUDIOFORMATSDIALOG_H

/* Dependencies */
#include <QDialog>
#include "ui_audio_formats.h"

/**
 * @brief The AudioFormatsDialog class
 */
class AudioFormatsDialog : public QDialog, protected Ui::AudioFormatsDialog
{
    Q_OBJECT

public:
    explicit AudioFormatsDialog(QWidget *parent = 0);
    virtual ~AudioFormatsDialog();
};

#endif // AUDIOFORMATSDIALOG_H
