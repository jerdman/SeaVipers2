#include "PanTilt.h"


PanTilt::PanTilt(QObject *parent):QObject(parent)
{
	port = new QSerialPort(this);
}


PanTilt::~PanTilt(void)
{
	port->close();
}

void PanTilt::connectPort(QString name){
	if(!port->isOpen()){
		connect(port, SIGNAL(readyRead()), SLOT(handleReadyRead()));
		port->setPortName(name);
		port->open(QIODevice::ReadWrite);
		port->setBaudRate(QSerialPort::Baud9600);
		port->setDataBits(QSerialPort::Data8);
		port->setParity(QSerialPort::NoParity);
		port->setStopBits(QSerialPort::OneStop);
		port->setFlowControl(QSerialPort::NoFlowControl);

		//setTerseFeedback();
		
	}
}

void PanTilt::handleReadyRead(void){
	QString response(port->readLine());
	// good command response starts with '*'
	// bad/error response starts with '!'

	if(response.startsWith("PP")){
		// parse and update

	} else if(response.startsWith('!')){
		// do something with this message
	} else {
		// badly formatted response
		// what do?
	}
	
}

void PanTilt::sendCommand(QString command){
	command.append(" ");
	port->write(command.toStdString().c_str());
}

void PanTilt::setSlaveMode(void){
	this->sendCommand("S");
}

void PanTilt::setImmediateMode(void){
	this->sendCommand("I");
}

void PanTilt::sendAwait(void){
	this->sendCommand("A");
}

void PanTilt::sendHalt(void){
	this->sendCommand("H"); // halt all motion
}

void PanTilt::sendReset(void){
	this->sendCommand("R"); // system reset
}

void PanTilt::setTerseFeedback(void){
	this->sendCommand("FT"); // set feedback mode to terse
	this->sendCommand("EE"); // command echo enablede
}

void PanTilt::panAbsolute(int p){
	this->sendCommand(QString("PP").append(QString::number(p)));
}

void PanTilt::tiltAbsolute(int t){
	this->sendCommand(QString("TP").append(QString::number(t)));
}

void PanTilt::panRelative(int p){
	this->sendCommand(QString("PO").append(QString::number(p)));
}

void PanTilt::tiltRelative(int t){
	this->sendCommand(QString("TO").append(QString::number(t)));
}