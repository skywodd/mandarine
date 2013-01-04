/* Includes */
#include <QUrl>
#include <QMenu>
#include <QString>
#include <QFileDialog>
#include <QModelIndex>
#include <QContextMenuEvent>
#include "playlistcontrols.h"

PlaylistControls::PlaylistControls(QWidget *parent) :
    QWidget(parent), m_playlistTableModel(0)
{
    /* Setup UI */
    setupUi(this);
    m_playlistTableModel = new PlaylistTableModel(this);

    /* Connect buttons signals to slots */
    connect(playlist_controls_new, &QAbstractButton::clicked, this, &PlaylistControls::handleNewPlaylist);
    connect(playlist_controls_load, &QAbstractButton::clicked, this, &PlaylistControls::handleLoadPlaylist);
    connect(playlist_controls_save, &QAbstractButton::clicked, this, &PlaylistControls::handleSavePlaylist);
    connect(playlist_controls_search, &QLineEdit::textEdited, this, &PlaylistControls::handleSearchPlaylist);

    /* Connect Tableview signals to slots */
    connect(playlist_controls_view, &QAbstractItemView::doubleClicked, this, &PlaylistControls::handleDoubleClick);
    connect(playlist_controls_view, &QTableViewClickable::rightClicked, this, &PlaylistControls::handleRightClicked);

    /* Set TableView source data's model */
    playlist_controls_view->setModel(m_playlistTableModel);
}

PlaylistControls::~PlaylistControls()
{
    /* Free memory */
    delete m_playlistTableModel;
}

void PlaylistControls::handleNewPlaylist()
{
    /* Flush playlist view and model */
    m_playlistTableModel->flush();

    /* Warm parent for new playlist */
    emit newPlaylist();
}

void PlaylistControls::handleLoadPlaylist()
{
    /* Prompt user */
    QString filename = QFileDialog::getOpenFileName(this, tr("Ouvrir une playlist ..."), "", tr("Ficher de playlist (*.*)"));

    /* Check if user has selected a file or not */
    if(filename.isEmpty())
        return;

    /* Warm parent for load playlist */
    emit loadPlaylist(QUrl(filename));
}

void PlaylistControls::handleSavePlaylist()
{
    /* Prompt user */
    QString filename = QFileDialog::getSaveFileName(this, tr("Sauvegarder une playlist ..."), "", tr("Ficher de playlist (*.*)"));

    /* Check if user has selected a file or not */
    if(filename.isEmpty())
        return;

    /* Warm parent for load playlist */
    emit savePlaylist(QUrl(filename));
}

void PlaylistControls::goToCurrentIndex()
{
    /* Select the currently played row */
    playlist_controls_view->selectRow(m_playlistTableModel->getCurrentIndex());
}

void PlaylistControls::setCurrentIndex(int pos)
{
    /* Set the currently played row */
    m_playlistTableModel->setCurrentIndex(pos);

    /* Warm parent for change the current index*/
    emit currentIndexChanged(pos);
}

void PlaylistControls::addMedia(const PlaylistTableModel::RowData_t &media)
{
    /* add the media at the end of the playlist */
    m_playlistTableModel->addRow(media);
}

void PlaylistControls::removeMedia(int pos)
{
    /* If the media is currently played */
    if(pos == m_playlistTableModel->getCurrentIndex())
    {
        m_playlistTableModel->setCurrentIndex(-1);
    }

    /* Remove the media */
    m_playlistTableModel->removeRow(pos);

    /* Warm playlist for remove */
    emit mediaRemoved(pos);
}

void PlaylistControls::handleSearchPlaylist(const QString& text)
{
    /* Process each rows */
    for(int i = 0; i < m_playlistTableModel->rowCount(); ++i)
    {
        /* Check if row need to be hidden or not */
        if(m_playlistTableModel->hasToBeHidden(i, text))
            playlist_controls_view->hideRow(i);
        else
            playlist_controls_view->showRow(i);
    }
}

void PlaylistControls::handleDoubleClick(const QModelIndex &index)
{
    /* Play the selected row */
    setCurrentIndex(index.row());
}

void PlaylistControls::handleRightClicked(QContextMenuEvent *event)
{
    /* Get the index at the right click position */
    QModelIndex index = playlist_controls_view->indexAt(event->pos());

    /* Check if the index is valid */
    if (index.isValid())
    {
        /* Select the row associated with the index */
        playlist_controls_view->selectRow(index.row());

        /* Create a contextual menu */
        QMenu contextualMenu(this);

        /* Craft menu's items */
        QAction* setCurrentIndex = contextualMenu.addAction(tr("lire"));
        QAction* deleteIndex = contextualMenu.addAction(tr("supprimer"));

        /* Disable "play" entry if the media is currently played */
        if (index.row() == m_playlistTableModel->getCurrentIndex())
            setCurrentIndex->setEnabled(false);

        /* Connect menu signals to slots */
        connect(setCurrentIndex, &QAction::triggered, this, &PlaylistControls::handleContextualMenuPlay);
        connect(deleteIndex, &QAction::triggered, this, &PlaylistControls::handleContextualMenuRemove);

        /* Show menu at the current cursor position */
        contextualMenu.exec(QCursor().pos());

        /* Disconnect menu signals */
        disconnect(setCurrentIndex, &QAction::triggered, this, &PlaylistControls::handleContextualMenuPlay);
        disconnect(deleteIndex, &QAction::triggered, this, &PlaylistControls::handleContextualMenuRemove);
    }
}

void PlaylistControls::handleContextualMenuPlay()
{
    /* Get the current selection */
    QItemSelectionModel *select = playlist_controls_view->selectionModel();

    /* Check if something is selected */
    if(select->selectedRows().size()) {

        /* Force-play the selected row */
        setCurrentIndex(select->selectedRows().front().row());
    }
}

void PlaylistControls::handleContextualMenuRemove()
{
    /* Get the current selection */
    QItemSelectionModel *select = playlist_controls_view->selectionModel();

    /* Check if something is selected */
    if(select->selectedRows().size()) {

        /* Force-play the selected row */
        removeMedia(select->selectedRows().front().row());
    }
}

