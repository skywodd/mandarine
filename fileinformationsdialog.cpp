/* Includes */
#include "fileinformationsdialog.h"

FileInformationsDialog::FileInformationsDialog(QMediaResource *source, QWidget *parent) :
    QDialog(parent)
{
    /* Setup UI */
    setupUi(this);

    /* Check if media is null */
    if(source->isNull())
        return;

    /* Show ressource informations */
    file_info_path->setText(source->url().toString());
    file_info_bitrate->setText(QString("%1Kbps").arg(source->audioBitRate() / 8 / 1024));
    file_info_codec->setText(source->audioCodec());
    file_info_nb_channels->setText(QString("%1").arg(source->channelCount()));
    qint64 size = source->dataSize();
    if(size < 1024UL) {
        file_info_size->setText(QString("%1o").arg(size));
    } else if(size < 1048576UL) {
        file_info_size->setText(QString("%1Kio").arg(size / 1024UL));
    } else if(size < 1073741824UL) {
        file_info_size->setText(QString("%1Mio").arg(size / 1048576UL));
    } else {
        file_info_size->setText(tr("gros CMB"));
    }
    file_info_sample_rate->setText(QString("%1KHz").arg(source->sampleRate() / 1000));
}

FileInformationsDialog::~FileInformationsDialog()
{
}


