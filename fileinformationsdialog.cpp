/* Includes */
#include <QWidget>
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
    file_info_path->setText(source->url().toString(QUrl::PrettyDecoded | QUrl::DecodeReserved));
    file_info_bitrate->setText(QString("%1 Kbps").arg(source->audioBitRate()));
    file_info_codec->setText(source->audioCodec());
    file_info_nb_channels->setText(QString("%1").arg(source->channelCount()));
    qint64 size = source->dataSize();
    if(size < 1024UL) {
        file_info_size->setText(QString("%1 o").arg(size));
    } else if(size < 1048576UL) {
        file_info_size->setText(QString("%1 Kio").arg((double) size / 1024UL, 0, 'f', 2));
    } else if(size < 1073741824UL) {
        file_info_size->setText(QString("%1 Mio").arg((double) size / 1048576UL, 0, 'f', 2));
    } else {
        file_info_size->setText(tr("gros CMB !"));
    }
    file_info_sample_rate->setText(QString("%1 Hz").arg(source->sampleRate()));
}


