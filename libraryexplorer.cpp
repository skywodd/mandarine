/* Includes */
#include <QStringList>
#include <QMessageBox>
#include <QDirIterator>
#include <QCursor>
#include <QAction>
#include <QPoint>
#include <QDebug>
#include <QMenu>
#include <QDir>
#include "libraryexplorer.h"

/* Sql */
#include <QSqlQuery>
#include <QSqlTableModel>

/* Taglib includes */
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

LibraryExplorer::LibraryExplorer(QWidget *parent) :
    QWidget(parent), m_databaseReady(false), m_displayMode(DISPLAY_MUSIC)
{
    /* Setup UI */
    setupUi(this);

    /* Connect gui signals to slots */
    connect(library_search_button, &QAbstractButton::clicked, this, &LibraryExplorer::handleReseach);
    connect(library_search_input, &QLineEdit::returnPressed, this, &LibraryExplorer::handleReseach);
    connect(library_explorer_displaymode, &QAbstractButton::clicked, this, &LibraryExplorer::handleDisplayMode);
    connect(library_explorer_tree, &QTreeViewClickable::customContextMenuRequested, this, &LibraryExplorer::handleRightClick);
    connect(library_explorer_tree, &QTreeViewClickable::customContextMenuRequested, [this]() {
        qDebug() << "library_explorer_tree::customContextMenuRequested -> LibraryExplorer[this]::handleRightClick";
    });
}

LibraryExplorer::~LibraryExplorer()
{
}

void LibraryExplorer::openDatabase(const QString &filename)
{
    qDebug() << "-> LibraryExplorer::openDatabase(" << filename << ")";

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
    qDebug() << "-> LibraryExplorer::addFile(" << filename << ")";

    /* Open file using taglib */
    TagLib::FileRef f(filename.toStdString().c_str());
    if(f.isNull() || f.tag() == 0)
        return;

    qDebug() << "LibraryExplorer::addFile - isNotNull";

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

    /* Refresh display */
    refresh(QString(""));
}

void LibraryExplorer::addFiles(const QStringList &filenames)
{
    qDebug() << "-> LibraryExplorer::addFiles(...)";

    /* For each filenames */
    foreach(QString filename, filenames)
    {
        addFile(filename);
    }
}

void LibraryExplorer::addDirectory(const QString &path)
{
    qDebug() << "-> LibraryExplorer::addDirectory(" << path << ")";

    /* Open the directory */
    QDirIterator iterator(QDir(path).absolutePath(), QDirIterator::Subdirectories);

    /* Process all audio files */
    while (iterator.hasNext()) {
        iterator.next();

        /* Try to add the current file */
        if (!iterator.fileInfo().isDir()) {
            addFile(iterator.filePath());
        }
    }
}

void LibraryExplorer::addDirectories(const QStringList &paths)
{
    qDebug() << "-> LibraryExplorer::addDirectories(" << paths.join(" ") << ")";

    /* For each directory */
    foreach(QString path, paths)
    {
        addDirectory(path);
    }
}

void LibraryExplorer::setDisplayMode(const LibraryExplorer::DisplayMode_t mode)
{
    qDebug() << "-> LibraryExplorer::setDisplayMode(" << mode << ")";

    /* Set the new display mode */
    m_displayMode = mode;

    /* Refresh the display */
    refresh(QString(""));
}

void LibraryExplorer::searchBy(const QString &terms, const LibraryExplorer::DisplayMode_t mode)
{
    qDebug() << "-> LibraryExplorer::searchBy(" << terms << ", " << mode << ")";

    /* Set the new display mode */
    m_displayMode = mode;

    /* Refresh the display with filter */
    refresh(terms);
}

void LibraryExplorer::refresh(const QString &filter)
{
    qDebug() << "-> LibraryExplorer::refresh(" << filter << ")";

    /* Refresh only if the database is ready */
    if(!m_databaseReady)
        return;

    /* Refresh with the correct display mode */
    switch(m_displayMode) {
    case DISPLAY_MUSIC:
        refreshMusic(filter);
        break;

    case DISPLAY_ALBUM:
        refreshAlbum(filter);
        break;

    case DISPLAY_ARTIST:
        refreshArtist(filter);
        break;

    case DISPLAY_GENRE:
        refreshGenre(filter);
        break;
    }
}

void LibraryExplorer::refreshMusic(const QString &music)
{
    qDebug() << "-> LibraryExplorer::refreshMusic(" << music << ")";

    QSqlTableModel *model = new QSqlTableModel(this, m_db);
    model->setTable("musics");
    if(music != QString(""))
        model->setFilter(QString("title LIKE \"%%1%\"").arg(music)); // SQl injection TODO
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Path"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Album"));
    model->setHeaderData(3, Qt::Horizontal, tr("Artist"));
    model->setHeaderData(4, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(5, Qt::Horizontal, tr("Year"));

    /* Display the model */
    library_explorer_tree->setModel(model);
    library_explorer_tree->hideColumn(0);
}

void LibraryExplorer::refreshAlbum(const QString &album)
{
    qDebug() << "-> LibraryExplorer::refreshAlbum(" << album << ")";
}

void LibraryExplorer::refreshArtist(const QString &artist)
{
    qDebug() << "-> LibraryExplorer::refreshArtist(" << artist << ")";
}

void LibraryExplorer::refreshGenre(const QString &genre)
{
    qDebug() << "-> LibraryExplorer::refreshGenre(" << genre << ")";
}

void LibraryExplorer::handleReseach()
{
    qDebug() << "-> LibraryExplorer::handleReseach()";

    /* Create a contextual menu */
    QMenu contextualMenu(this);

    /* Craft menu's items */
    QAction* displayMusic = contextualMenu.addAction(tr("Recherche par musiques"));
    QAction* displayAlbum = contextualMenu.addAction(tr("Recherche par albums"));
    QAction* displayArtist = contextualMenu.addAction(tr("Recherche par artistes"));
    QAction* displayGenre = contextualMenu.addAction(tr("Recherche par genres"));

    /* Connect menu signals to slots */
    connect(displayMusic, &QAction::triggered, [this]() {
        qDebug() << "-> LibraryExplorer::handleReseachMusic()";
        searchBy(library_search_input->text(), DISPLAY_MUSIC);
    });
    connect(displayAlbum, &QAction::triggered, [this]() {
        qDebug() << "-> LibraryExplorer::handleReseachAlbum()";
        searchBy(library_search_input->text(), DISPLAY_ALBUM);
    });
    connect(displayArtist, &QAction::triggered, [this]() {
        qDebug() << "-> LibraryExplorer::handleReseachArtist()";
        searchBy(library_search_input->text(), DISPLAY_ARTIST);
    });
    connect(displayGenre, &QAction::triggered, [this]() {
        qDebug() << "-> LibraryExplorer::handleReseachGenre()";
        searchBy(library_search_input->text(), DISPLAY_GENRE);
    });

    /* Show menu at the current cursor position */
    contextualMenu.exec(QCursor().pos());
}

void LibraryExplorer::handleRightClick(const QPoint& pos)
{
    qDebug() << "-> LibraryExplorer::handleRightClick([" << pos.x() << ", "<< pos.y() << "])";

    /* Get the index at the right click position */
    QModelIndex index = library_explorer_tree->indexAt(pos);

    /* Check if the index is valid */
    if (index.isValid())
    {
        qDebug() << "-> LibraryExplorer::handleRightClick - isValid";

        // TODO
    }
}

void LibraryExplorer::handleDisplayMode()
{
    qDebug() << "-> LibraryExplorer::handleDisplayMode()";

    /* Create a contextual menu */
    QMenu contextualMenu(this);

    /* Craft menu's items */
    QAction* displayMusic = contextualMenu.addAction(tr("Affichage par musiques"));
    QAction* displayAlbum = contextualMenu.addAction(tr("Affichage par albums"));
    QAction* displayArtist = contextualMenu.addAction(tr("Affichage par artistes"));
    QAction* displayGenre = contextualMenu.addAction(tr("Affichage par genres"));

    /* Check current display mode */
    switch(m_displayMode) {
    case DISPLAY_MUSIC:
        displayMusic->setCheckable(true);
        displayMusic->setChecked(true);
        break;

    case DISPLAY_ALBUM:
        displayAlbum->setCheckable(true);
        displayAlbum->setChecked(true);
        break;

    case DISPLAY_ARTIST:
        displayArtist->setCheckable(true);
        displayArtist->setChecked(true);
        break;

    case DISPLAY_GENRE:
        displayGenre->setCheckable(true);
        displayGenre->setChecked(true);
        break;
    }

    /* Connect menu signals to slots */
    connect(displayMusic, &QAction::triggered, [this]() {
        qDebug() << "-> LibraryExplorer::handleDisplayModeMusic()";
        setDisplayMode(DISPLAY_MUSIC);
    });
    connect(displayAlbum, &QAction::triggered, [this]() {
        qDebug() << "-> LibraryExplorer::handleDisplayModeAlbum()";
        setDisplayMode(DISPLAY_ALBUM);
    });
    connect(displayArtist, &QAction::triggered, [this]() {
        qDebug() << "-> LibraryExplorer::handleDisplayModeArtist()";
        setDisplayMode(DISPLAY_ARTIST);
    });
    connect(displayGenre, &QAction::triggered, [this]() {
        qDebug() << "-> LibraryExplorer::handleDisplayModeGenre()";
        setDisplayMode(DISPLAY_GENRE);
    });

    /* Show menu at the current cursor position */
    contextualMenu.exec(QCursor().pos());
}
