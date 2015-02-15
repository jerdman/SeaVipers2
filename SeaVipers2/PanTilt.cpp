#include "PanTilt.h"


PanTilt::PanTilt(QObject *parent):QObject(parent)
{
	port = new QSerialPort(this);
	pan = 0;
	tilt = 0;
	emit panChanged(pan);
	emit tiltChanged(tilt);
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
		setImmediateMode();
	}
}

void PanTilt::handleReadyRead(void){
	QString response(port->readLine());
	// good command response starts with '*'
	// bad/error response starts with '!'

	if(response.startsWith('*')){
		// parse and update

	} else if(response.startsWith('!')){
		// do something with this message
	} else {
		// this->sendReset();
	}
	
}

void PanTilt::sendCommand(QString command){
	command.append(" ");
	if(port->isOpen())
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
	if(p > right)
		pan = right;
	else if(p < left)
		pan = left;
	else
		pan = p;
	emit panChanged(pan);
	this->sendCommand(QString("PP").append(QString::number(pan)));
}

void PanTilt::tiltAbsolute(int t){
	if(t > up)
		tilt = up;
	else if(t < down)
		tilt = down;
	else
		tilt = t;
	emit tiltChanged(tilt);
	this->sendCommand(QString("TP").append(QString::number(tilt)));
}

void PanTilt::panRelative(int p){
	if(pan + p > right)
		pan = right;
	else if(pan + p < left)
		pan = left;
	else
		pan += p;
	emit panChanged(pan);
	this->sendCommand(QString("PO").append(QString::number(p)));
}

void PanTilt::tiltRelative(int t){
	if(tilt + t > up)
		tilt = up;
	else if(tilt + t < down)
		tilt = down;
	else 
		tilt += down;
	emit tiltChanged(tilt);
	this->sendCommand(QString("TO").append(QString::number(t)));
}

int PanTilt::getPan(void){
	return this->pan;
}

int PanTilt::getTilt(void){
	return this->tilt;
}