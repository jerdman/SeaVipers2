#pragma once
#include <QtSerialPort\QSerialPort>

class PanTilt : public QObject
{
	Q_OBJECT

private:
	QSerialPort *port;

public:
	PanTilt(QObject *parent = 0);
	~PanTilt(void);
};

