#ifndef RUNCOMMAND_H
#define RUNCOMMAND_H

#include "qprocess.h"
#include <QThread>

class RunCommand : public QThread {
	Q_OBJECT
public:
    explicit RunCommand(QObject *parent = nullptr, QString command = nullptr) : QThread(parent), command(command) { }
protected:
	void run() override {
		QString result = command;
		QProcess download_process;
		download_process.setProcessChannelMode(QProcess::MergedChannels);
        emit outputLine("> " + command);

		QObject::connect(&download_process, &QProcess::readyReadStandardOutput, [&download_process, &result, this]() {
			QByteArray output = download_process.readAllStandardOutput();
			// ui->shell_output->append(output);
			// qDebug() << "Output:" << output;
			emit outputLine(output);
			result.append(output);
		});
		/*

		QObject::connect(&download_process, &QProcess::finished, [&](int exitCode, QProcess::ExitStatus exitStatus) {
			qDebug() << "Process finished with exit code:" << exitCode << "and status:" << exitStatus;
			// delete this;
		});
		*/
		/* ... here is the expensive or blocking operation ... */
		download_process.startCommand(command);
		download_process.waitForFinished(-1);
		emit resultReady(result);
	}
private:
	QString command;
signals:
	void resultReady(QString s);
	void outputLine(const QString& s);
};
#endif // RUNCOMMAND_H
