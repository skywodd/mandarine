/* Includes */
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QDir>
#include <QDirIterator>
#include <QMenu>
#include <QCursor>
#include <QAction>
#include "libraryexplorer.h"

/* Taglib includes */
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

LibraryExplorer::LibraryExplorer(QWidget *parent) :
    QWidget(parent), m_databaseReady(false), m_displayMode(DISPLAY_ALBUM)
{
    /* Setup UI */
    setupUi(this);

    /* Connect gui signals to slots */
    connect(library_search_button, &QAbstractButton::clicked, this, &LibraryExplorer::handleReseach);
    connect(library_search_input, &QLineEdit::returnPressed, this, &LibraryExplorer::handleReseach);
    connect(library_explorer_displaymode, &QAbstractButton::clicked, this, &LibraryExplorer::handleDisplayMode);
    connect(library_explorer_tree, &QTreeViewClickable::rightClicked, this, &LibraryExplorer::handleRightClick);
}

LibraryExplorer::~LibraryExplorer()
{
}

void LibraryExplorer::openDatabase(const QString &filename)
{
    /* Init. database link */
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(filename);
    db.setUserName("root");
    db.setPassword("");

    /* Open database */
    if(!db.open())
    {
        /* Drop error message (critical) and exit */
        QMessageBox::critical(this, QString(tr("Erreur interne")), QString(tr("Impossible d'ouvrir le fichier de base de données !")));
        exit(1);
    }

    /* Prepare database structure if freshly created */
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS \"musics\" (\"path\" TEXT PRIMARY KEY, \"title\" TEXT, \"album\" TEXT, \"artist\" TEXT, \"genre\" TEXT, \"year\" TEXT)");
    query.exec();

    /* Database ready ! */
    m_databaseReady = true;
}

void LibraryExplorer::addFile(const QString &filename)
{
    /* Open file using taglib */
    TagLib::FileRef f(filename.toStdString().c_str());
    if(f.isNull() || f.tag() == 0)
        return;

    /* Get file properties */
    TagLib::String title = f.tag()->title();
    TagLib::String album = f.tag()->album();
    TagLib::String artist = f.tag()->artist();
    TagLib::String genre = f.tag()->genre();
    TagLib::uint year = f.tag()->year();

    /* Add them to the database */
    QSqlQuery query;
    query.prepare(QString("INSERT INTO \"musics\" VALUES(\"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\")").arg(filename, QString(title.toCString()), QString(album.toCString()), QString(artist.toCString()), QString(genre.toCString())).arg(year));
    query.exec();
}

void LibraryExplorer::addFiles(const QStringList &filenames)
{
    /* For each filenames */
    foreach(QString filename, filenames)
    {
        addFile(filename);
    }
}

void LibraryExplorer::addDirectories(const QString &path)
{
    /* Open the directory */
    QDirIterator iterator(QDir(path).absolutePath(), QDirIterator::Subdirectories);

    /* Process all audio files */
    while (iterator.hasNext()) {
        iterator.next();

        /* Try to add the current file */
        if (!iterator.fileInfo().isDir()) {
            addFile(iterator.fileName());
        }
    }
}

void LibraryExplorer::setDisplayMode(const LibraryExplorer::DisplayMode_t mode)
{
    /* Set the new display mode */
    m_displayMode = mode;

    /* Refresh the display */
    refresh();
}

void LibraryExplorer::refresh()
{
    /* Refresh only if the database is ready */
    if(!m_databaseReady)
        return;

    /* Clear the current tree view */
    //library_explorer_tree->
}

void LibraryExplorer::handleReseach()
{
    // TODO
}

void LibraryExplorer::handleRightClick(QContextMenuEvent *event)
{
    /* Get the index at the right click position */
    QModelIndex index = library_explorer_tree->indexAt(event->pos());

    /* Check if the index is valid */
    if (index.isValid())
    {
        // TODO
    }
}

void LibraryExplorer::handleDisplayMode()
{
    /* Create a contextual menu */
    QMenu contextualMenu(this);

    /* Craft menu's items */
    QAction* displayMusic = contextualMenu.addAction(tr("Par musiques"));
    QAction* displayAlbum = contextualMenu.addAction(tr("Par albums"));
    QAction* displayArtist = contextualMenu.addAction(tr("Par artistes"));
    QAction* displayGenre = contextualMenu.addAction(tr("Par genres"));

    /* Connect menu signals to slots */
    connect(displayMusic, &QAction::triggered, this, &LibraryExplorer::handleDisplayModeMusic);
    connect(displayAlbum, &QAction::triggered, this, &LibraryExplorer::handleDisplayModeAlbum);
    connect(displayArtist, &QAction::triggered, this, &LibraryExplorer::handleDisplayModeArtist);
    connect(displayGenre, &QAction::triggered, this, &LibraryExplorer::handleDisplayModeGenre);

    /* Show menu at the current cursor position */
    contextualMenu.exec(QCursor().pos());

    /* Disconnect menu signals */
    disconnect(displayMusic, &QAction::triggered, this, &LibraryExplorer::handleDisplayModeMusic);
    disconnect(displayAlbum, &QAction::triggered, this, &LibraryExplorer::handleDisplayModeAlbum);
    disconnect(displayArtist, &QAction::triggered, this, &LibraryExplorer::handleDisplayModeArtist);
    disconnect(displayGenre, &QAction::triggered, this, &LibraryExplorer::handleDisplayModeGenre);
}

void LibraryExplorer::handleDisplayModeMusic()
{
    /* Set the display mode */
    setDisplayMode(DISPLAY_MUSIC);
}

void LibraryExplorer::handleDisplayModeAlbum()
{
    /* Set the display mode */
    setDisplayMode(DISPLAY_ALBUM);
}

void LibraryExplorer::handleDisplayModeArtist()
{
    /* Set the display mode */
    setDisplayMode(DISPLAY_ARTIST);
}

void LibraryExplorer::handleDisplayModeGenre()
{
    /* Set the display mode */
    setDisplayMode(DISPLAY_GENRE);
}
