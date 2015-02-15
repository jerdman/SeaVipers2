#ifndef SEAVIPERS2_H
#define SEAVIPERS2_H

#include <QtWidgets/QMainWindow>
#include "ui_seavipers2.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <TLD.h>
#include <QTimer>
#include <QImage>
#include <QPainter>
#include <QtGui>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <Rangefinder.h>
#include <PanTilt.h>



class SeaVipers2 : public QMainWindow
{
	Q_OBJECT

public:
	SeaVipers2(QWidget *parent = 0);
	~SeaVipers2();

private:
	static const int xOff = 10;
	static const int yOff = 10;

	int frame;
	Ui::SeaVipers2Class ui;
	cv::VideoCapture vidcap;
	tld::TLD tracker;
	QBasicTimer video_timer;
	bool tracking;
	cv::Mat current_mat, grey, rgb;
	QRect bb, img_area;
	QPoint origin;
	bool selecting;

	QString filepath;

	Rangefinder *ranger;
	PanTilt *ptu;

	QFile outputFile;
	QTextStream outputStream;

	QPoint imgCenter, bbCenter;

	double dxpp, dypp;

	double target_range;
	double target_heading;

public slots:
	void handleOpenCamera(void);
	void handleStartTracker(void);
	void handleLearningBoxChecked(void);
	void handleResetButtonClicked(void);

protected:
	void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
};

#endif // SEAVIPERS2_H
