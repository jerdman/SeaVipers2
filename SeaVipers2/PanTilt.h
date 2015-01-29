#pragma once
#include <QtSerialPort\QSerialPort>

class PanTilt : public QObject
{
	Q_OBJECT

private:
	QSerialPort *port;
	int pan; // -26133 left limit, 26133 right limit
	int tilt; // -27999 down limit, 28000 up limit 
	static const int up = 28000;
	static const int down = -27999;
	static const int left = -26133;
	static const int right = 26133;

signals:
	void panChanged(int p);
	void tiltChanged(int t);

public slots:
	void handleReadyRead(void);

public:
	PanTilt(QObject *parent = 0);
	~PanTilt(void);

	void connectPort(QString name);
	void sendCommand(QString command);

	void setSlaveMode(void);
	void setImmediateMode(void);
	void sendAwait(void);
	void sendHalt(void);
	void sendReset(void);
	void setTerseFeedback(void);

	void panAbsolute(int p);
	void tiltAbsolute(int t);
	void panRelative(int p);
	void tiltRelative(int t);
};

