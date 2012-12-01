/**
 * TODO
 */

/* Includes */
#include <QtGui>
#include "mainwindow.h"

/**
 * Program entry point
 *
 * @param argc CLI arguments count
 * @param argv CLI arguments array
 * @return Error code (if any)
 */
int main(int argc, char** argv) {

	/* Initialize application */
	QApplication app(argc, argv);
    app.setApplicationName("Mandarine");
	app.setQuitOnLastWindowClosed(true);

	/* Instantiate and show main windows */
	MainWindow window;
	window.show();

	/* Return exit code when all windows are closed */
	return app.exec();
}
