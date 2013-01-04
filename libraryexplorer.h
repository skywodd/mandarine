#ifndef LIBRARYEXPLORER_H
#define LIBRARYEXPLORER_H

/* Dependencies */
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
     * Default construtor of the widget
     *
     * @brief LibraryExplorer
     * @param parent Parent widget
     */
    explicit LibraryExplorer(QWidget *parent = 0);

    /**
     * Default destructor of the widget
     *
     * @brief ~LibraryExplorer
     * @remarks Ready for overload
     */
    virtual ~LibraryExplorer();

    // setDatabaseLink(link)

protected:
    // m_databaseLink

signals:
    // addMediaToPlaylist()

public slots:
    // addFiles()
    // addDirectories()

protected slots:
    void handleReseach();
    void handleRightClick();
    void handleDisplayMode();
    void handleDisplayModeMusic();
    void handleDisplayModeAlbum();
    void handleDisplayModeArtist();
    void handleDisplayModeGenre();
};

#endif // LIBRARYEXPLORER_H
