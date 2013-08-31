#ifndef LIBRARYEXPLORER_H
#define LIBRARYEXPLORER_H

/* Dependencies */
#include <QWidget>
#include <QString>
#include <QSqlDatabase>
#include "playlisttablemodel.h"
#include "ui_libraryexplorer.h"

/* Forward declaration */
class QStringList;
class QPoint;

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

    /** Database link */
    QSqlDatabase m_db;

signals:
    /**
     * Signal emitted when user want to add file to the playlist
     *
     * @brief addMediaToPlaylist
     * @param filename Audio file path to add
     */
    void addMediaToPlaylist(const QString& filename, const PlaylistTableModel::RowData_t& infos);

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
     * @brief addDirectory
     * @param path Directory path to scan for files
     */
    void addDirectory(const QString& path);

    /**
     * Scan a bunch of directories for audio files
     *
     * @brief addDirectories
     * @param paths Directories path to scan for files
     */
    void addDirectories(const QStringList &paths);

    /**
     * Set the current display mode
     *
     * @brief setDisplayMode
     * @param mode The new display mode
     */
    void setDisplayMode(const DisplayMode_t mode);

    /**
     * Search in tree view according specified search terms
     *
     * @brief searchBy
     * @param terms Terms to search
     * @param mode Display / Search mode
     */
    void searchBy(const QString& terms, const DisplayMode_t mode);

    void refresh(const QString& filter);

protected slots:
    void handleAddMedia();
    void refreshMusic(const QString& music);
    void refreshFiltered(const QString& filter, const QString& mask);
    void handleReseach();
    void handleRightClick(const QPoint& pos);
    void handleDisplayMode();
};

#endif // LIBRARYEXPLORER_H
