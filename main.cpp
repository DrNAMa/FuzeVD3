#include "MainWindow.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

    // Used for QSettings
    QCoreApplication::setOrganizationName("Fuze page");
    QCoreApplication::setOrganizationDomain("fuze.page");
    QCoreApplication::setApplicationName("FuzeVD");
    QCoreApplication::setApplicationVersion("3.0.0");

	QTranslator translator;
	const QStringList uiLanguages = QLocale::system().uiLanguages();
	for (const QString &locale : uiLanguages) {
		const QString baseName = "FuzeVD3_" + QLocale(locale).name();
		if (translator.load(":/i18n/" + baseName)) {
			a.installTranslator(&translator);
			break;
		}
	}
	MainWindow w;
	w.show();
	return a.exec();
}
