/**
 * @file metaexplorer.h
 * @brief Meta data display widget
 * @author Fabien Batteix & Jordan Vertaure
 * @version 1.0
 *
 * @section intro_sec Introduction
 * This file contain all stuff required to instantiate MetaExplorer object.\n
 * The MetaExplorer object is designed as a widget and used to display meta data informations.\n
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
#ifndef METAEXPLORER_H
#define METAEXPLORER_H

/* Dependencies */
#include <QWidget>
#include "ui_metaexplorer.h"
#include <QString>

/* Forward declarations */
class QMediaResource;
class QNetworkAccessManager;
class QNetworkReply;
class QVariant;
class QUrl;

/**
 * @brief Meta data display widget
 *
 * The class is designed to display meta data's informations retrieved from ID3 tags.\n
 * \n
 * The widget can display the following informations :\n
 * - Album cover (from url or embedded source)\n
 * - Standard informations (title, album, artist, ...)\n
 * - Technical informations (file size, codec, number of channels, ...)
 */
class MetaExplorer : public QWidget, protected Ui::MetaExplorer
{
    Q_OBJECT
    
public:
    /**
     * Default constructor of the widget
     *
     * @brief MetaExplorer constructor
     * @param parent Parent widget
     */
    explicit MetaExplorer(QWidget *parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief MetaExplorer destructor
     * @remarks Ready for overload
     */
    virtual ~MetaExplorer();

protected:
    /** "No image" icon ressource location */
    static const QString m_noimage;

    /** "Image loading" icon ressource location  */
    static const QString m_imageloading;

    /** True if the widget can display QMediaContent informations, false otherwise */
    bool m_isReady;

    /** Cover image state */
    enum {
        NO_COVER, /*!< No cover at all */
        LARGE_COVER_OK, /*!< Large cover from url on screen */
        SMALL_COVER_OK, /*!< Small cover from url on screen */
        EMBEDDED_COVER_OK, /*!< Embedded cover from file on screen */
        EXTERNAL_COVER_OK /*!< External cover from file on screen */
    } m_coverState;

    /** QMediaResource pointer for technical informations's display */
    const QMediaResource* m_qressource;

    /** Network manager */
    QNetworkAccessManager* m_manager;

public slots:
    /**
     * Bind QMediaResource pointer to the widget for display
     *
     * @brief bindQMediaRessource
     * @param content QMediaResource pointer to display
     */
    void bindQMediaRessource(const QMediaResource* ressource);

    /**
     * Display meta data informations
     *
     * @brief displayMetaInfo
     * @param meta Meta informations key
     * @param data Meta informations data
     */
    void displayMetaInfo(const QString& meta, const QVariant& data);

    /**
     * Display cover from external file
     *
     * @brief displayExternalCover
     * @param path External image file's path
     */
    void displayExternalCover(const QString& path);

    /**
     * Reset the widget in his default state
     *
     * @brief reset
     */
    void reset();

protected slots:

    /**
     * Handle button to display file informations
     *
     * @brief handleFileInfosShow
     */
    void handleFileInfosShow();

    /**
     * Get cover from the web
     *
     * @brief getCoverImage
     * @param url Source image url
     */
    void getCoverImage(const QUrl& url);

    /**
     * Handle termination of a network request (for cover)
     *
     * @brief handleNetworkFinished
     * @param reply Received reply
     */
    void handleNetworkFinished(QNetworkReply* reply);
};

#endif // METAEXPLORER_H
