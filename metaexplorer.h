#ifndef METAEXPLORER_H
#define METAEXPLORER_H

/* Dependencies */
#include <QVariant>
#include <QString>
#include "ui_metaexplorer.h"

/* Forward declaration */
class QMediaResource;
class QNetworkAccessManager;
class QNetworkReply;

/**
 * @brief Meta information's widget
 *
 * The class is designed to display meta information retrieved from ID3 tags.
 * \n
 * The widget can display :
 * - Album cover (from url or embedded source)
 * - Standard informations (title, album, artist, ...)
 * - Technical informations (file size, codec, number of channels, ...)
 */
class MetaExplorer : public QWidget, protected Ui::MetaExplorer
{
    Q_OBJECT
    
public:
    /**
     * Default constructor of the MetaExplorer widget
     *
     * @brief MetaExplorer constructor
     * @param parent Parent widget
     */
    explicit MetaExplorer(QWidget *parent = 0);

    /**
     * Default destructor of the MetaExplorer widget
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

    /** QMediaResource pointer for technical informations's display */
    QMediaResource* m_qressource;

    /** Network manager */
    QNetworkAccessManager* m_manager;

public slots:
    /**
     * Bind QMediaContent pointer to the widget for display
     *
     * @brief bindQMediaContent
     * @param content QMediaContent pointer to display
     */
    void bindQMediaContent(QMediaResource* ressource);

    /**
     * Display meta informations
     *
     * @brief displayMetaInfo
     * @param meta Meta informations key
     * @param data Meta informations value
     */
    void displayMetaInfo(const QString& meta, const QVariant& data);

    /**
     * Reset the widget in default state
     *
     * @brief reset
     */
    void reset();

protected slots:

    /**
     * Handle clicked signal from meta_file_info button
     *
     * @brief handleFileInfosShow
     */
    void handleFileInfosShow();

    /**
     * Get cover from the web
     *
     * @brief getCoverImage
     * @param url Cover source url
     */
    void getCoverImage(const QUrl& url);

    /**
     * Handle termination of network request (for cover)
     *
     * @brief handleNetworkFinished
     * @param reply Received reply
     */
    void handleNetworkFinished(QNetworkReply* reply);

};

#endif // METAEXPLORER_H
