/*
 * See header file for details
 *
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 *
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 *
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */

// Includes
#include <QMessageBox>
#include "mainwindow.h"
#include "aboutdialog.h"
#include "audioformatsdialog.h"
#include "audiointerfacesdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    // Setup Ui
    setupUi(this);

    // Connect menu signals to slots
    // Menu music
    connect(action_play, SIGNAL(triggered()), SLOT(play()));
    connect(action_stop, SIGNAL(triggered()), SLOT(stop()));
    connect(action_fast_forward, SIGNAL(triggered()), SLOT(fastForward()));
    connect(action_fast_rewind, SIGNAL(triggered()), SLOT(fastRewind()));
    connect(action_next_music, SIGNAL(triggered()), SLOT(next()));
    connect(action_previous_music, SIGNAL(triggered()), SLOT(previous()));
    connect(action_mute, SIGNAL(triggered()), SLOT(mute()));

    // Menu library
    connect(action_add_file, SIGNAL(triggered()), SLOT(addFiles()));
    connect(action_add_directory, SIGNAL(triggered()), SLOT(addDirectory()));
    connect(action_add_network, SIGNAL(triggered()), SLOT(addNetwork()));

    // Menu playlist
    connect(action_new_playlist, SIGNAL(triggered()), SLOT(newPlaylist()));
    connect(action_open_playlist, SIGNAL(triggered()), SLOT(openPlaylist()));
    connect(action_save_playlist, SIGNAL(triggered()), SLOT(savePlaylist()));
    connect(action_loop_disable, SIGNAL(triggered()), SLOT(loopDisable()));
    connect(action_loop_music, SIGNAL(triggered()), SLOT(loopMusic()));
    connect(action_loop_playlist, SIGNAL(triggered()), SLOT(loopPlaylist()));
    connect(action_random_disable, SIGNAL(triggered()), SLOT(randomDisable()));
    connect(action_random_library, SIGNAL(triggered()), SLOT(randomLibrary()));
    connect(action_random_playlist, SIGNAL(triggered()), SLOT(randomPlaylist()));
    connect(action_go_to_playing, SIGNAL(triggered()), SLOT(goToPlaying()));
    connect(action_flush_playlist, SIGNAL(triggered()), SLOT(flushPlaylist()));
    connect(action_mix_playlist, SIGNAL(triggered()), SLOT(mixPlaylist()));

    // Menu tools
    connect(action_show_equalizer, SIGNAL(triggered()), SLOT(showEqualizerDialog()));
    connect(action_enable_fft, SIGNAL(toggled(bool)), SLOT(enableFFT(bool)));
    connect(action_refresh_database, SIGNAL(triggered()), SLOT(showDatabaseUpdateDialog()));
    connect(action_cleanup_database, SIGNAL(triggered()), SLOT(showDatabaseCleanupDialog()));
    connect(action_show_setup, SIGNAL(triggered()), SLOT(showSetupDialog()));
    connect(action_show_hardware, SIGNAL(triggered()), SLOT(showAudioInterfacesDialog()));
    connect(action_show_formats, SIGNAL(triggered()), SLOT(showSupportedFormatsDialog()));

    // Menu help
    connect(action_show_help, SIGNAL(triggered()), SLOT(showHelpDialog()));
    connect(action_show_about, SIGNAL(triggered()), SLOT(showAboutDialog()));
    connect(action_show_aboutqt, SIGNAL(triggered()), SLOT(showQtAboutDialog()));

    // Library tab
    // TODO class file_explorer
    connect(file_explorer_previous, SIGNAL(clicked()), SLOT());
    connect(file_explorer_next, SIGNAL(clicked()), SLOT());
    connect(file_explorer_up, SIGNAL(clicked()), SLOT());
    connect(file_explorer_home, SIGNAL(clicked()), SLOT());
    connect(file_explorer_path, SIGNAL(returnPressed()), SLOT());

    // Fichier tab
    connect(library_search_button, SIGNAL(clicked()), SLOT(searchLibrary()));
    connect(library_search_input, SIGNAL(returnPressed()), SLOT(searchLibrary()));

    // Playlist & search buttons
    connect(playlist_new_button, SIGNAL(clicked()), SLOT(newPlaylist()));
    connect(playlist_load_button, SIGNAL(clicked()), SLOT(openPlaylist()));
    connect(playlist_save_button, SIGNAL(clicked()), SLOT(savePlaylist()));
    connect(playlist_search_button, SIGNAL(clicked()), SLOT(searchPlaylist()));
    connect(playlist_search_input, SIGNAL(returnPressed()), SLOT(searchPlaylist()));

    // Controls buttons
    connect(controls_play_button, SIGNAL(clicked()), SLOT(play()));
    connect(controls_stop_button, SIGNAL(clicked()), SLOT(stop()));
    connect(controls_fast_forward_button, SIGNAL(clicked()), SLOT(fastForward()));
    connect(controls_fast_rewind_button, SIGNAL(clicked()), SLOT(fastRewind()));
    connect(controls_previous_button, SIGNAL(clicked()), SLOT(previous()));
    connect(controls_next_button, SIGNAL(clicked()), SLOT(next()));
    connect(controls_time_slider, SIGNAL(sliderMoved(int)), SLOT(changeTimeSeek(int)));
    connect(controls_volume_slider, SIGNAL(sliderMoved(int)), SLOT(changeVolume(int)));
    connect(controls_random_button, SIGNAL(clicked()), SLOT(showRandomMenu()));
    connect(controls_loop_button, SIGNAL(clicked()), SLOT(showLoopMenu()));

    //connect(controls_, SIGNAL(), SLOT());

    // Create MediaObjects
    player = new QMediaPlayer();
    playlist = new QMediaPlaylist();
}

MainWindow::~MainWindow(void) {
    delete player;
    delete playlist;
}

void MainWindow::play() {

}

void MainWindow::pause() {

}

void MainWindow::stop() {

}

void MainWindow::next() {

}

void MainWindow::previous() {

}

void MainWindow::fastForward() {

}

void MainWindow::fastRewind() {

}

void MainWindow::mute() {
    player->setVolume(0);
    controls_volume_slider->setValue(0);
    controls_volume_label->setText("0%");
}

void MainWindow::changeVolume(int volume) {
    player->setVolume(volume);
    controls_volume_label->setText(QString("%1%%").arg(volume));
}

void MainWindow::changeTimeSeek(int timeseek) {

}

void MainWindow::addFiles() {

}

void MainWindow::addDirectory() {

}

void MainWindow::addNetwork() {

}

void MainWindow::newPlaylist() {

}

void MainWindow::openPlaylist() {

}

void MainWindow::savePlaylist() {

}

void MainWindow::showLoopMenu()
{
}

void MainWindow::loopDisable() {

}

void MainWindow::loopMusic() {

}

void MainWindow::loopPlaylist() {

}

void MainWindow::showRandomMenu()
{
}

void MainWindow::randomDisable() {

}

void MainWindow::randomPlaylist() {

}

void MainWindow::randomLibrary() {

}

void MainWindow::goToPlaying()
{
}

void MainWindow::flushPlaylist() {

}

void MainWindow::mixPlaylist() {

}

void MainWindow::searchPlaylist() {

}

void MainWindow::searchLibrary() {

}

void MainWindow::enableFFT(bool enable) {

}

void MainWindow::showHelpDialog() {
    // TODO or not
    QMessageBox::about(this, tr("Aide ..."), tr("Si vous êtes en train de lire cette phrase c'est qu'il y a un probléme quelque part, dommage :)"));
}

void MainWindow::showAboutDialog() {
    AboutDialog about(this);
    about.exec();
}

void MainWindow::showQtAboutDialog() {
    QMessageBox::aboutQt(this, tr("A propos de Qt ..."));
}

void MainWindow::showAudioInterfacesDialog() {
    // TODO
    AudioInterfacesDialog dialog(this);
    dialog.exec();
}

void MainWindow::showSupportedFormatsDialog() {
    // TODO
    AudioFormatsDialog dialog(this);
    dialog.exec();
}

void MainWindow::showDatabaseCleanupDialog() {
    // TODO
}

void MainWindow::showDatabaseUpdateDialog() {
    // TODO
}

void MainWindow::showEqualizerDialog() {
    // TODO
}

void MainWindow::showSetupDialog() {
    // TODO
}
