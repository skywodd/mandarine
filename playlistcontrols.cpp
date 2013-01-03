/* Includes */
#include <QUrl>
#include <QFileDialog>
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

    /* Set TableView source data's model */
    playlist_controls_view->setModel(&m_playlistTableModel);
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

