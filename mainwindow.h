/**
 * @file mainwindow.h
 * @brief The main window header class
 * @author SkyWodd & jordanVertaure
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This class is designed to handle all features of the music player.\n
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* Dependencies */
#include <QMainWindow>
#include <QWidget>

#include "ui_mainwindow.h"

// TODO

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow, protected Ui::MainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    
protected:

protected slots:
    void show_about_dialog();
    void show_qtabout_dialog();
    void show_audio_interfaces_dialog();
    void show_database_cleanup_dialog();
    void show_database_update_dialog();
    void show_equalizer_dialog();
};

#endif // MAINWINDOW_H
