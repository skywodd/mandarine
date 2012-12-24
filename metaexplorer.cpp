/* Includes */
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMediaResource>
#include <QMediaMetaData>
#include <QDebug>
#include "metaexplorer.h"
#include "fileinformationsdialog.h"

/* Static members initialization */
const QString MetaExplorer::m_noimage(":/cover/image_missing.png");
const QString MetaExplorer::m_imageloading(":/cover/image_loading.png");

MetaExplorer::MetaExplorer(QWidget *parent) :
    QWidget(parent), m_isReady(false), m_qressource(0), m_manager(0)
{
    /* Setup UI */
    setupUi(this);

    /* Allocate network manager instance */
    m_manager = new QNetworkAccessManager(this);

    /* Connect button signal to handler slot */
    connect(meta_file_info, &QAbstractButton::clicked, this, &MetaExplorer::handleFileInfosShow);
    connect(m_manager, &QNetworkAccessManager::finished, this, &MetaExplorer::handleNetworkFinished);
}

MetaExplorer::~MetaExplorer()
{
    /* Free memory */
    delete m_manager;
}

void MetaExplorer::bindQMediaContent(QMediaResource *ressource)
{
    /* Store pointer and turn on "ready" flag */
    m_isReady = true;
    m_qressource = ressource;
}

void MetaExplorer::displayMetaInfo(const QString& meta, const QVariant& data)
{
    /* Switch according received meta information */
    if (meta == QMediaMetaData::Title) { /* Title */
        meta_info_title->setText(data.toString());

    } else if (meta == QMediaMetaData::AlbumTitle) { /* Album title */
        meta_info_album->setText(data.toString());

    } else if (meta == QMediaMetaData::Author) { /* Author list */
        meta_info_author->setText(data.toStringList().join(", "));

    } else if (meta == QMediaMetaData::Genre) { /* Genre list */
        meta_info_type->setText(data.toStringList().join(", "));

    } else if (meta == QMediaMetaData::Year) { /* Year */
        meta_info_year->setText(QString("%1").arg(data.toInt()));

    } else if (meta == QMediaMetaData::Comment) { /* Comments */
        meta_info_comment->setText(data.toString());

    } else if (meta == QMediaMetaData::CoverArtImage) { /* Cover (embedded) */
        meta_info_cover->setPixmap(QPixmap::fromImage(data.value<QImage>()));

    } else if (meta == QMediaMetaData::CoverArtUrlLarge) { /* Cover (url) */
        getCoverImage(data.toUrl());

    } else if (meta == QMediaMetaData::CoverArtUrlSmall) { /* cover (url) */
        getCoverImage(data.toUrl());

    } else { /* Other meta (debug) */
        qDebug() << "Skipped meta: " << meta;
    }
}

void MetaExplorer::reset()
{
    /* Reset widget state */
    m_isReady = false;
    meta_info_cover->setPixmap(QPixmap(m_noimage));
    meta_info_title->setText("");
    meta_info_album->setText("");
    meta_info_author->setText("");
    meta_info_type->setText("");
    meta_info_year->setText("");
    meta_info_comment->setText("");
}

void MetaExplorer::handleFileInfosShow()
{
    /* Check if widget can display technical information */
    if(m_isReady)
    {

        /* Display the audio file information dialog */
        FileInformationsDialog infoDialog(m_qressource, this);
        infoDialog.exec();
    }
}

void MetaExplorer::getCoverImage(const QUrl &url)
{
    /* Craft network request */
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, QString("Mozilla/6.0 (Windows NT 6.2; WOW64; rv:16.0.1) Gecko/20121011 Firefox/16.0.1"));

    /* Display loading icon */
    meta_info_cover->setPixmap(QPixmap(m_imageloading));

    /* Send request */
    m_manager->get(request);
}

void MetaExplorer::handleNetworkFinished(QNetworkReply* reply)
{
    /* Check for error */
    if(reply->error() != QNetworkReply::NoError) {

        /* Display the "no image" icon */
        meta_info_cover->setPixmap(QPixmap(m_noimage));
        return;
    }

    /* Get the data */
    QByteArray imgData = reply->readAll();
    QPixmap pixmap;

    /* Display the cover */
    pixmap.loadFromData(imgData);
    meta_info_cover->setPixmap(pixmap);

    /* Close the request */
    reply->close();
}
