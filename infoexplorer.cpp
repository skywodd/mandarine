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

/* Includes */
#include <QUrl>
#include <QDebug>
#include <QString>
#include "infoexplorer.h"

InfoExplorer::InfoExplorer(QWidget *parent) :
    QWidget(parent)
{
    /* Setup UI */
    setupUi(this);
}

InfoExplorer::~InfoExplorer()
{
}

void InfoExplorer::displayInfo(const QString& search)
{
    qDebug() << "-> InfoExplorer::displayInfo(" << search << ")";

    /* Open the mobile version of the Wikipedia page for the specified search terms */
    info_explorer_webview->load(QUrl(QString("http://en.m.wikipedia.org/wiki/Main_Page/?search=%1").arg(search)));
}
