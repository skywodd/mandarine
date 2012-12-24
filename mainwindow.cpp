/* Includes */
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include "mainwindow.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    /* Setup UI */
    setupUi(this);

    /* Connect signals to slots */
    connect(action_show_help, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(action_show_about, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(action_show_aboutqt, &QAction::triggered, this, &MainWindow::showQtAboutDialog);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showHelpDialog()
{
    QMessageBox::about(this, tr("Aide"), tr("Désolé mais pour le moment vous devez vous démerder tous seul :)"));
}

void MainWindow::showAboutDialog()
{
    AboutDialog about(this);
    about.exec();
}

void MainWindow::showQtAboutDialog()
{
    QMessageBox::aboutQt(this, tr("A propos de Qt"));
}
