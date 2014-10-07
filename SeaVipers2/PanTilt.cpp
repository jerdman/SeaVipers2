#include "PanTilt.h"


PanTilt::PanTilt(QObject *parent):QObject(parent)
{
	port = new QSerialPort(this);
}


PanTilt::~PanTilt(void)
{
	port->close();
}
