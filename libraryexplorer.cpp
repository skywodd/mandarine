/* Includes */
#include <QContextMenuEvent>
#include "libraryexplorer.h"

LibraryExplorer::LibraryExplorer(QWidget *parent) :
    QWidget(parent)
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

void LibraryExplorer::handleReseach()
{
}

void LibraryExplorer::handleRightClick()
{
}

void LibraryExplorer::handleDisplayMode()
{
}

void LibraryExplorer::handleDisplayModeMusic()
{
}

void LibraryExplorer::handleDisplayModeAlbum()
{
}

void LibraryExplorer::handleDisplayModeArtist()
{
}

void LibraryExplorer::handleDisplayModeGenre()
{
}
