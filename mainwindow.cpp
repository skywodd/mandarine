/*
 * See header file for details
 *
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 *
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 *
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */

// Includes
#include "mainwindow.h"
#include "ui_about.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Setup Ui
    setupUi(this);

    // Connect menu signals to slots
    // TODO

}

MainWindow::~MainWindow(void)
{
    // TODO
}

void MainWindow::show_about_dialog()
{
}

void MainWindow::show_qtabout_dialog()
{
}

void MainWindow::show_audio_interfaces_dialog()
{
}

void MainWindow::show_database_cleanup_dialog()
{
}

void MainWindow::show_database_update_dialog()
{
}

void MainWindow::show_equalizer_dialog()
{
}
