#pragma once

#include <QtSerialPort/QSerialPort>

class Rangefinder : public QObject{
	Q_OBJECT

private:
	double distance;
	QSerialPort *port;
	bool reporting;

signals:
	void distanceChanged(double d);

public slots:
	void handleReadyRead(void);

public:
	Rangefinder(QObject *parent = 0);
	~Rangefinder(void);

	void connectPort(QString name);
	void disconnectPort(void);
	bool isConnected(void);

	void startReporting(void);
	void stopReporting(void);
	void checkStatus(void);

	double getDistance(void);

};

