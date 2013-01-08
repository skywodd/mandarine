/* Includes */
#include <QStringList>
#include <QMessageBox>
#include <QDirIterator>
#include <QCursor>
#include <QAction>
#include <QPoint>
#include <QMenu>
#include <QDir>
#include "libraryexplorer.h"

/* Sql */
#include <QSqlQuery>

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
    connect(library_explorer_tree, &QTreeViewClickable::customContextMenuRequested, this, &LibraryExplorer::handleRightClick);
}

LibraryExplorer::~LibraryExplorer()
{
}

void LibraryExplorer::openDatabase(const QString &filename)
{
    /* Init. database link */
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("localhost");
    m_db.setDatabaseName(filename);
    m_db.setUserName("root");
    m_db.setPassword("");

    /* Open database */
    if(!m_db.open())
    {
        /* Drop error message (critical) and exit */
        QMessageBox::critical(this, QString(tr("Erreur interne")), QString(tr("Impossible d'ouvrir le fichier de base de données !")));
        exit(1);
    }

    /* Prepare database structure if freshly created */
    QSqlQuery query(m_db);
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
    QSqlQuery query(m_db);
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

void LibraryExplorer::addDirectory(const QString &path)
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

void LibraryExplorer::addDirectories(const QString &paths)
{
    /* For each directory */
    foreach(QString path, paths)
    {
        addDirectory(path);
    }
}

void LibraryExplorer::setDisplayMode(const LibraryExplorer::DisplayMode_t mode)
{
    /* Set the new display mode */
    m_displayMode = mode;

    /* Refresh the display */
    refresh();
}

void LibraryExplorer::searchBy(const QString &terms, const LibraryExplorer::DisplayMode_t mode)
{
    // TODO
}

void LibraryExplorer::refresh()
{
    /* Refresh only if the database is ready */
    if(!m_databaseReady)
        return;

    /* Clear the current tree view */
    //TODO
}

void LibraryExplorer::handleReseach()
{
    /* Create a contextual menu */
    QMenu contextualMenu(this);

    /* Craft menu's items */
    QAction* displayMusic = contextualMenu.addAction(tr("Recherche par musiques"));
    QAction* displayAlbum = contextualMenu.addAction(tr("Recherche par albums"));
    QAction* displayArtist = contextualMenu.addAction(tr("Recherche par artistes"));
    QAction* displayGenre = contextualMenu.addAction(tr("Recherche par genres"));

    /* Connect menu signals to slots */
    connect(displayMusic, &QAction::triggered, [this]() {
        searchBy(library_search_input->text(), DISPLAY_MUSIC);
    });
    connect(displayAlbum, &QAction::triggered, [this]() {
        searchBy(library_search_input->text(), DISPLAY_ALBUM);
    });
    connect(displayArtist, &QAction::triggered, [this]() {
        searchBy(library_search_input->text(), DISPLAY_ARTIST);
    });
    connect(displayGenre, &QAction::triggered, [this]() {
        searchBy(library_search_input->text(), DISPLAY_GENRE);
    });

    /* Show menu at the current cursor position */
    contextualMenu.exec(QCursor().pos());
}

void LibraryExplorer::handleRightClick(const QPoint& pos)
{
    /* Get the index at the right click position */
    QModelIndex index = library_explorer_tree->indexAt(pos);

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
    QAction* displayMusic = contextualMenu.addAction(tr("Affichage par musiques"));
    QAction* displayAlbum = contextualMenu.addAction(tr("Affichage par albums"));
    QAction* displayArtist = contextualMenu.addAction(tr("Affichage par artistes"));
    QAction* displayGenre = contextualMenu.addAction(tr("Affichage par genres"));

    /* Connect menu signals to slots */
    connect(displayMusic, &QAction::triggered, [this]() {
        setDisplayMode(DISPLAY_MUSIC);
    });
    connect(displayAlbum, &QAction::triggered, [this]() {
        setDisplayMode(DISPLAY_ALBUM);
    });
    connect(displayArtist, &QAction::triggered, [this]() {
        setDisplayMode(DISPLAY_ARTIST);
    });
    connect(displayGenre, &QAction::triggered, [this]() {
        setDisplayMode(DISPLAY_GENRE);
    });

    /* Show menu at the current cursor position */
    contextualMenu.exec(QCursor().pos());
}
