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

public slots:
	void handleOpenCamera(void);
	void handleStartTracker(void);
	void handleLearningBoxChecked(void);

protected:
	void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
};

#endif // SEAVIPERS2_H
