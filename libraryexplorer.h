#ifndef LIBRARYEXPLORER_H
#define LIBRARYEXPLORER_H

/* Dependencies */
#include <QWidget>
#include <QString>
#include <QStringList>
#include "ui_libraryexplorer.h"

/**
 * @brief LibraryExplorer display widget
 *
 * This class is designed as a QWidget for displaying library content.
 * The widget internaly use a SQL database to store and retrieve data.
 */
class LibraryExplorer : public QWidget, protected Ui::LibraryExplorer
{
    Q_OBJECT
    
public:
    /**
     * Display modes enum
     */
    typedef enum
    {
        DISPLAY_MUSIC, /*!< Display by music */
        DISPLAY_ALBUM, /*!< Display by album */
        DISPLAY_ARTIST, /*!< Display by artist */
        DISPLAY_GENRE /*!< Display by genre */
    } DisplayMode_t;

    /**
     * Default constructor of the widget
     *
     * @brief LibraryExplorer constructor
     * @param parent Parent widget
     */
    explicit LibraryExplorer(QWidget *parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief LibraryExplorer destructor
     * @remarks Ready for overload
     */
    virtual ~LibraryExplorer();

    /**
     * Open database file
     *
     * @brief openDatabase
     * @param filename Database file path
     */
    void openDatabase(const QString& filename = QString("database.db"));

protected:
    /** True when the database is ready */
    bool m_databaseReady;

    /** Display mode */
    DisplayMode_t m_displayMode;

signals:
    /**
     * Signal emitted when user want to add file to the playlist
     *
     * @brief addMediaToPlaylist
     * @param filename Audio file path to add
     */
    void addMediaToPlaylist(const QString& filename);

public slots:
    /**
     * Add a single file to the library
     *
     * @brief addFile
     * @param filename Filename to add
     */
    void addFile(const QString& filename);

    /**
     * Add a bunch of files to the library
     *
     * @brief addFiles
     * @param filenames Filename list to add
     */
    void addFiles(const QStringList& filenames);

    /**
     * Scan a directory and his sub-directory for audio files
     *
     * @brief addDirectories
     * @param path Directory to scan for files
     */
    void addDirectories(const QString& path);

    /**
     * Set the current display mode
     *
     * @brief setDisplayMode
     * @param mode The new display mode
     */
    void setDisplayMode(const DisplayMode_t mode);

protected slots:
    void refresh();
    void handleReseach();
    void handleRightClick(QContextMenuEvent *event);
    void handleDisplayMode();
    void handleDisplayModeMusic();
    void handleDisplayModeAlbum();
    void handleDisplayModeArtist();
    void handleDisplayModeGenre();
};

#endif // LIBRARYEXPLORER_H
