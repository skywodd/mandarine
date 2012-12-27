#include <QUrl>

#include "infoexplorer.h"

InfoExplorer::InfoExplorer(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    showInformation("LiSA");
}

InfoExplorer::~InfoExplorer()
{
}

void InfoExplorer::showInformation(const QString &album)
{
    //Open the mobile Wikipedia Page
    info_explorer_webview->load( QUrl( QString("http://en.m.wikipedia.org/wiki/Main_Page/?search=%1").arg(album) ) );

}
