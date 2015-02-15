#include "Rangefinder.h"


Rangefinder::Rangefinder(QObject *parent): QObject(parent){
	port = new QSerialPort(this);
	reporting = false;
	distance = 0;
}


Rangefinder::~Rangefinder(void)
{
	disconnectPort();
}

void Rangefinder::connectPort(QString name){
	if(!port->isOpen()){
		connect(port, SIGNAL(readyRead()), SLOT(handleReadyRead()));
		port->setPortName(name);
		port->open(QIODevice::ReadWrite);
		port->setBaudRate(QSerialPort::Baud19200);
		port->setDataBits(QSerialPort::Data8);
		port->setParity(QSerialPort::NoParity);
		port->setStopBits(QSerialPort::OneStop);
		port->setFlowControl(QSerialPort::NoFlowControl);

		port->write("M\r"); // report distance in meters
	}
}

void Rangefinder::disconnectPort(void){
	if(port->isOpen())
		stopReporting();
	port->close();
}

bool Rangefinder::isConnected(void){
	return port->isOpen();
}

void Rangefinder::handleReadyRead(void){
	QString response(port->readLine());
	if(response.startsWith("DIST:")){
		// DIST:XXXX.YYU
		double d = response.midRef(5,7).toDouble();
		if(distance != d){
			distance = d;
			emit distanceChanged(distance);
		}
	}
}

void Rangefinder::startReporting(void){
	if(port->isOpen()){
		port->write("R\r"); // continuous averaged ranged mode, 10 Hz
		reporting = true;
	}
}

void Rangefinder::stopReporting(void){
	reporting = false;
	if(port->isOpen())
		port->write("O\r"); // stop continuous reporting
}

double Rangefinder::getDistance(void){
	return this->distance;
}