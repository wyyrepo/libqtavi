#include <QApplication>
#include "ExportDialog.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	ExportDialog dialog;
#ifdef Q_OS_ANDROID
	dialog.showMaximized();
#else
	dialog.show();
#endif

	app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
	return app.exec();
}
