/* Includes */
#include <QUrl>
#include <QFileDialog>
#include <QMenu>
#include <QModelIndex>
#include <QContextMenuEvent>
#include <QDebug>
#include <QDrag>
#include "playlistcontrols.h"

PlaylistControls::PlaylistControls(QWidget *parent) :
    QWidget(parent), m_playlistTableModel(0)
{
    /* Setup UI */
    setupUi(this);

    /* Connect button signals to slots */
    connect(playlist_controls_new, &QAbstractButton::clicked, this, &PlaylistControls::handleNewPlaylist);
    connect(playlist_controls_load, &QAbstractButton::clicked, this, &PlaylistControls::handleLoadPlaylist);
    connect(playlist_controls_save, &QAbstractButton::clicked, this, &PlaylistControls::handleSavePlaylist);
    connect(playlist_controls_search, &QLineEdit::textEdited, this, &PlaylistControls::handleSearchPlaylist);

    /* Connect Tableview signals to slots */
    connect(playlist_controls_view, &QAbstractItemView::doubleClicked, this, &PlaylistControls::handleDoubleClick);
    connect(playlist_controls_view, &QTableViewClickable::rightClicked, this, &PlaylistControls::handleRightClicked);

    /* Set TableView source data's model */
    playlist_controls_view->setModel(&m_playlistTableModel);


    PlaylistTableModel::RowData_t musique1, musique2;
    musique1.title = QString("titre1");
    musique1.album = QString("album1");
    musique1.authors = QString("artistre1");
    musique1.genre = QString("genre1");
    musique1.duration = QString("durée1");
    musique2.title = QString("titre2");
    musique2.album = QString("album2");
    musique2.authors = QString("artistre2");
    musique2.genre = QString("genre2");
    musique2.duration = QString("durée2");
    m_playlistTableModel.addRow(musique1);
    m_playlistTableModel.addRow(musique2);
    m_playlistTableModel.setCurrentIndex(0);
    m_playlistTableModel.moveRow(0,1);

}

PlaylistControls::~PlaylistControls()
{
}

void PlaylistControls::handleNewPlaylist()
{
    /* Flush playlist view and model */
    m_playlistTableModel.flush();

    /* Warm parent for new playlist */
    emit newPlaylist();
}

void PlaylistControls::handleLoadPlaylist()
{
    /* Prompt user */
    QString filename = QFileDialog::getOpenFileName(this, tr("Ouvrir une playlist ..."), "", tr("Ficher de playlist (*.*)"));

    /* check if user has selected a file or not */
    if(filename.isEmpty())
        return;

    /* Warm parent for load playlist */
    emit loadPlaylist(QUrl(filename));
}

void PlaylistControls::handleSavePlaylist()
{
    /* Prompt user */
    QString filename = QFileDialog::getSaveFileName(this, tr("Sauvegarder une playlist ..."), "", tr("Ficher de playlist (*.*)"));

    /* check if user has selected a file or not */
    if(filename.isEmpty())
        return;

    /* Warm parent for load playlist */
    emit savePlaylist(QUrl(filename));
}

void PlaylistControls::goToCurrentIndex()
{
    /* Select the currently played row */
    playlist_controls_view->selectRow(m_playlistTableModel.getCurrentIndex());
}

void PlaylistControls::setCurrentIndex(int pos)
{
    /* Set the currently played row */
    m_playlistTableModel.setCurrentIndex(pos);

    /* Warm parent for change the current index*/
    emit currentIndexChanged(pos);
}

void PlaylistControls::addMedia(const PlaylistTableModel::RowData_t &media)
{
    /* add the media at the end of the playlist */
    m_playlistTableModel.addRow(media);
}

void PlaylistControls::removeMedia(int pos)
{
    /* If the row was current index */
    if ( pos == m_playlistTableModel.getCurrentIndex())
    {
        m_playlistTableModel.setCurrentIndex(-1);
        emit mediaRemoved(pos);
    }

    /* remove the media at the pos if it exists */
    m_playlistTableModel.removeRow(pos);
}

void PlaylistControls::handleSearchPlaylist(const QString& text)
{
    /* Process each rows */
    for(int i = 0; i < m_playlistTableModel.rowCount(); ++i)
    {
        /* Check if row need to be hidden or not */
        if(m_playlistTableModel.hasToBeHidden(i, text))
            playlist_controls_view->hideRow(i);
        else
            playlist_controls_view->showRow(i);
    }
}

void PlaylistControls::handleDoubleClick(const QModelIndex &index)
{
    /* set the row double clicked as the current index */
    setCurrentIndex(index.row());

}

void PlaylistControls::handleRightClicked(QContextMenuEvent *event)
{
    QModelIndex index = playlist_controls_view->indexAt(event->pos());
    if (index.isValid())
    {
        playlist_controls_view->selectRow(index.row());

        QMenu contextualMenu(this);

        /* Craft menu items */
        QAction* setCurrentIndex = contextualMenu.addAction(tr("lire"));
        QAction* deleteIndex = contextualMenu.addAction(tr("supprimer"));

        /* Check the current index */
        if ( index.row() == m_playlistTableModel.getCurrentIndex())
            setCurrentIndex->setEnabled(false);

        /* Connect items signals to slots */
        connect(setCurrentIndex, &QAction::triggered, this, &PlaylistControls::handleContextualMenuPlay);
        connect(deleteIndex, &QAction::triggered, this, &PlaylistControls::handleContextualMenuRemove);

        /* Show menu at the current cursor position */
        contextualMenu.exec(QCursor().pos());

        /* Disconnect signals */
        disconnect(setCurrentIndex, &QAction::triggered, this, &PlaylistControls::handleContextualMenuPlay);
        disconnect(deleteIndex, &QAction::triggered, this, &PlaylistControls::handleContextualMenuRemove);
    }
}

void PlaylistControls::handleContextualMenuPlay()
{
    QItemSelectionModel *select = playlist_controls_view->selectionModel();
    QModelIndex index = select->selectedRows().front();
    setCurrentIndex(index.row());
}

void PlaylistControls::handleContextualMenuRemove()
{
    QItemSelectionModel *select = playlist_controls_view->selectionModel();
    QModelIndex index = select->selectedRows().front();
    removeMedia(index.row());
}

void PlaylistControls::dropEvent(QDropEvent *event)
{
     qDebug()<<"dropEvent";
}

void PlaylistControls::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug()<<"dragMoveEvent";
}

void PlaylistControls::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mousePressEvent";
}

void PlaylistControls::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"dragEnter";
}

void PlaylistControls::handleInternalMove(QDragEnterEvent *event)
{


}
