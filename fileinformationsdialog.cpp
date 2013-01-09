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
#include <QSize>
#include <QWidget>
#include <QDebug>
#include <QMediaResource>
#include "fileinformationsdialog.h"

FileInformationsDialog::FileInformationsDialog(QWidget* parent) :
    QDialog(parent)
{
    /* Setup UI */
    setupUi(this);
}

FileInformationsDialog::~FileInformationsDialog()
{
}

void FileInformationsDialog::displayInfo(const QMediaResource *source)
{
    /* Check if media is null */
    if(source->isNull())
        return;

    /* Display media informations */
    file_info_path->setText(source->url().toLocalFile());
    file_info_bitrate->setText(QString("%1 Kbps").arg(source->audioBitRate())); // TODO Bps or Kbps ?
    file_info_codec->setText(source->audioCodec());
    file_info_nb_channels->setText(QString("%1").arg(source->channelCount()));
    qint64 fsize = source->dataSize();
    if(fsize < 1024UL) {
        file_info_size->setText(QString("%1 o").arg(fsize));
    } else if(fsize < 1048576UL) {
        file_info_size->setText(QString("%1 Kio").arg((double) fsize / 1024UL, 0, 'f', 2));
    } else if(fsize < 1073741824UL) {
        file_info_size->setText(QString("%1 Mio").arg((double) fsize / 1048576UL, 0, 'f', 2));
    } else {
        file_info_size->setText(tr(">1Go"));
    }
    file_info_sample_rate->setText(QString("%1 Hz").arg(source->sampleRate()));
}


