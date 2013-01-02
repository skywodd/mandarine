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
    connect(playlist_controls_search, &QAbstractButton::clicked, this, &PlaylistControls::handleSearchPlaylist);

    playlist_controls_list->setModel( &m_playlistTableModel );


    QStringList musique1, musique2;
    musique1.push_back(QString("titre1"));
    musique1.push_back(QString("album1"));
    musique1.push_back(QString("artistre1"));
    musique1.push_back(QString("genre1"));
    musique1.push_back(QString("durée1"));
    musique2.push_back(QString("titre2"));
    musique2.push_back(QString("album2"));
    musique2.push_back(QString("artistre2"));
    musique2.push_back(QString("genre2"));
    musique2.push_back(QString("durée2"));
    m_playlistTableModel.addRow(0,musique1);
    m_playlistTableModel.addRow(1,musique2);
    m_playlistTableModel.setCurrentIndex(0);
    m_playlistTableModel.swapRow(0,1);

}

PlaylistControls::~PlaylistControls()
{
}

void PlaylistControls::handleNewPlaylist()
{
    m_playlistTableModel.flush();
    //TODO : réactualisation de la vue

}

void PlaylistControls::handleLoadPlaylist()
{

}

void PlaylistControls::handleSavePlaylist()
{

}

void PlaylistControls::handleSearchPlaylist()
{
    QString recherche = playlist_controls_search_input->text();
    for(int i=0; i <m_playlistTableModel.rowCount(); ++i)
    {
        QString str = m_playlistTableModel.getLine(i);
        if(str.contains(recherche, Qt::CaseInsensitive))
            playlist_controls_list->showRow(i);
        else
            playlist_controls_list->hideRow(i);
    }
}

