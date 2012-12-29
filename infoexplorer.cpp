/* Includes */
#include <QUrl>
#include "infoexplorer.h"

InfoExplorer::InfoExplorer(QWidget *parent) :
    QWidget(parent)
{
    /* Setup UI */
    setupUi(this);
}

InfoExplorer::~InfoExplorer()
{
}

void InfoExplorer::showInformation(const QString &album)
{
    /* Open the mobile version of the Wikipedia page for the specified search term */
    info_explorer_webview->load(QUrl(QString("http://en.m.wikipedia.org/wiki/Main_Page/?search=%1").arg(album)));
}
