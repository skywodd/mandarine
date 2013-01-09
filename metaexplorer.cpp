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
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMediaResource>
#include <QMediaMetaData>
#include <QVariant>
#include <QDebug>
#include <QUrl>
#include "metaexplorer.h"
#include "fileinformationsdialog.h"

/* Static members initialization */
const QString MetaExplorer::m_noimage(":/cover/image_missing.png");
const QString MetaExplorer::m_imageloading(":/cover/image_loading.png");

MetaExplorer::MetaExplorer(QWidget *parent) :
    QWidget(parent), m_isReady(false), m_coverState(NO_COVER),
    m_qressource(0), m_manager(0)
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

void MetaExplorer::bindQMediaRessource(const QMediaResource *ressource)
{
    qDebug() << "-> MetaExplorer::bindQMediaRessource(" << ressource << ")";

    /* Avoid memory leak */
    delete m_qressource;

    /* Store pointer and turn on "ready" flag */
    m_isReady = true;
    m_qressource = ressource;
}

void MetaExplorer::displayMetaInfo(const QString& meta, const QVariant& data)
{
    qDebug() << "-> MetaExplorer::displayMetaInfo(" << meta << ", ...)";

    /* Switch according the received meta key */
    if (meta == QMediaMetaData::Title) { /* Title */
        meta_info_title->setText(data.toString());
        qDebug() << "-> MetaExplorer::displayMetaInfo - Title" << meta_info_title->text();

    } else if (meta == QMediaMetaData::AlbumTitle) { /* Album title */
        meta_info_album->setText(data.toString());
        qDebug() << "-> MetaExplorer::displayMetaInfo - Album title" << meta_info_album->text();

    } else if (meta == QMediaMetaData::Author) { /* Author list */
        meta_info_author->setText(data.toStringList().join(", "));
        qDebug() << "-> MetaExplorer::displayMetaInfo - Author list" << meta_info_author->text();

    } else if (meta == QMediaMetaData::Genre) { /* Genre list */
        meta_info_type->setText(data.toStringList().join(", "));
        qDebug() << "-> MetaExplorer::displayMetaInfo - Genre list" << meta_info_type->text();

    } else if (meta == QMediaMetaData::Year) { /* Year */
        meta_info_year->setText(QString("%1").arg(data.toInt()));
        qDebug() << "-> MetaExplorer::displayMetaInfo - Year" << meta_info_year->text();

    } else if (meta == QMediaMetaData::Comment) { /* Comments */
        meta_info_comment->setText(data.toString());
        qDebug() << "-> MetaExplorer::displayMetaInfo - Comments" << meta_info_comment->text();

    } else if (meta == QMediaMetaData::CoverArtImage) { /* Cover (embedded) */

        /* Load the cover only if necessary */
        if(m_coverState == NO_COVER || m_coverState == SMALL_COVER_OK) {
            qDebug() << "-> MetaExplorer::displayMetaInfo - EMBEDDED_COVER";
            m_coverState = EMBEDDED_COVER_OK;
            meta_info_cover->setPixmap(QPixmap::fromImage(data.value<QImage>()).scaled(meta_info_cover->size(), Qt::KeepAspectRatio));
        }

    } else if (meta == QMediaMetaData::CoverArtUrlLarge) { /* Cover (url) */

        /* Download cover from web only if necessary */
        if(m_coverState == NO_COVER || m_coverState == SMALL_COVER_OK) {
            qDebug() << "-> MetaExplorer::displayMetaInfo - LARGE_COVER" << data.toUrl().toString();
            m_coverState = LARGE_COVER_OK;
            getCoverImage(data.toUrl());
        }

    } else if (meta == QMediaMetaData::CoverArtUrlSmall) { /* cover (url) */

        /* Download cover from web only if necessary */
        if(m_coverState == NO_COVER) {
            qDebug() << "-> MetaExplorer::displayMetaInfo - SMALL_COVER" << data.toUrl().toString();
            m_coverState = SMALL_COVER_OK;
            getCoverImage(data.toUrl());
        }

    } else { /* Other meta (debug) */
        qDebug() << "Ignored meta: " << meta;
    }
}

void MetaExplorer::reset()
{
    qDebug() << "-> MetaExplorer::reset()";

    /* Reset widget to his default state */
    m_isReady = false;
    m_coverState = NO_COVER;
    meta_info_cover->setPixmap(QPixmap(m_noimage));
    meta_info_title->setText("");
    meta_info_album->setText("");
    meta_info_author->setText("");
    meta_info_type->setText("");
    meta_info_year->setText("");
    meta_info_comment->setText("");
}

void MetaExplorer::displayExternalCover(const QString &path)
{
    qDebug() << "-> MetaExplorer::displayExternalCover(" << path << ")";

    /* Display external cover */
    QPixmap pixmap;
    if(pixmap.load(path))
    {
        qDebug() << "-> MetaExplorer::displayExternalCover - success";
        meta_info_cover->setPixmap(pixmap.scaled(meta_info_cover->size(), Qt::KeepAspectRatio));
        m_coverState = EXTERNAL_COVER_OK;
    }
        else
    {
        qDebug() << "-> MetaExplorer::displayExternalCover - failed";
        meta_info_cover->setPixmap(QPixmap(m_noimage));
        m_coverState = NO_COVER;
    }
}

void MetaExplorer::handleFileInfosShow()
{
    qDebug() << "-> MetaExplorer::handleFileInfosShow()";

    /* Check if the widget can display file informations */
    if(m_isReady)
    {
        qDebug() << "-> MetaExplorer::handleFileInfosShow - isReady";

        /* Display the audio file informations dialog */
        FileInformationsDialog infoDialog(this);
        infoDialog.displayInfo(m_qressource);
        infoDialog.exec();
    }
}

void MetaExplorer::getCoverImage(const QUrl& url)
{
    qDebug() << "-> MetaExplorer::getCoverImage(" << url.toString() << ")";

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
    qDebug() << "-> MetaExplorer::handleNetworkFinished(...)";

    /* Check for any error */
    if(reply->error() != QNetworkReply::NoError) {

        /* Display the "no image" icon */
        qDebug() << "-> MetaExplorer::handleNetworkFinished - failed";
        meta_info_cover->setPixmap(QPixmap(m_noimage));
        m_coverState = NO_COVER;
        return;
    }

    /* Get the image data */
    QByteArray imgData = reply->readAll();
    QPixmap pixmap;

    /* Display the cover */
    if(pixmap.loadFromData(imgData))
    {
        qDebug() << "-> MetaExplorer::handleNetworkFinished - success";
        meta_info_cover->setPixmap(pixmap.scaled(meta_info_cover->size(), Qt::KeepAspectRatio));
    }
        else
    {
        qDebug() << "-> MetaExplorer::handleNetworkFinished - failed";
        meta_info_cover->setPixmap(QPixmap(m_noimage));
        m_coverState = NO_COVER;
    }

    /* Close the request */
    reply->close();
}
