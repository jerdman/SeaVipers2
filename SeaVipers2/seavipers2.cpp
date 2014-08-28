#include "seavipers2.h"



SeaVipers2::SeaVipers2(QWidget *parent) : QMainWindow(parent){
	qDebug() << "Setting up main window";
	ui.setupUi(this);
	vidcap = cv::VideoCapture();
	video_timer = QBasicTimer();
	//tracker = tld::TLD();
	tracking = false;
	// TODO tld parameters
	// TODO connect signals/slots
	handleOpenCamera();
	frame = 0;

	//connections
	connect(ui.initializeButton, SIGNAL(clicked()), this, SLOT(handleStartTracker()));
	connect(ui.learningCheckBox, SIGNAL(clicked()), this, SLOT(handleLearningBoxChecked()));
}

SeaVipers2::~SeaVipers2() {
	vidcap.release();
}

void SeaVipers2::handleOpenCamera(void){
	qDebug() << "Opening Camera";
	vidcap.open(0);
	vidcap >> current_mat;
	vidcap >> current_mat;
	vidcap >> current_mat;
	vidcap >> current_mat;
	img_area = QRect(xOff, yOff, current_mat.cols, current_mat.rows);
	video_timer.start(1000.0/9.0, this); // 9 Hz
}

void SeaVipers2::handleStartTracker(void){
	//initialize tracker
	qDebug() << "Initializing Tracker...";
	cv::cvtColor(current_mat, grey, CV_BGR2GRAY);
	qDebug() << "Converted current to grey";
	tracker.detectorCascade->imgWidth = grey.cols;
	tracker.detectorCascade->imgHeight = grey.rows;
	tracker.detectorCascade->imgWidthStep = grey.step;
	qDebug() << "Detector Cascade params set";
	cv::Rect box = cv::Rect(bb.x() - xOff, bb.y() - yOff, bb.width(), bb.height());
	qDebug() << "cv::Rect created";
	tracker.selectObject(grey, &box);
	tracking = true;
	qDebug() << "...Initialization Complete";
}

void SeaVipers2::paintEvent(QPaintEvent *event){
	QWidget::paintEvent(event);
	QImage img;
	cv::cvtColor(current_mat, rgb, cv::COLOR_BGR2RGB);
	img = QImage(rgb.data, rgb.cols, rgb.rows, QImage::Format_RGB888);
	QPainter pnt(this);
	pnt.drawImage(xOff, yOff, img);
	pnt.setPen(Qt::green);
	pnt.drawRect(bb);
}

void SeaVipers2::timerEvent(QTimerEvent *event){
	if(event->timerId() == video_timer.timerId()){
		// get next frame
		vidcap >> current_mat;
		frame++;
		if(tracking){
			tracker.processImage(current_mat);
			//bb = QRect(tracker.currBB->x + xOff, tracker.currBB->y + yOff, tracker.currBB->width, tracker.currBB->height);
			if(tracker.currBB){
				bb.setLeft(tracker.currBB->x + xOff);
				bb.setTop(tracker.currBB->y + yOff);
				bb.setWidth(tracker.currBB->width);
				bb.setHeight(tracker.currBB->height);
			}
		}
		update(); // flags ready for QPaintEvent
	} else
		QWidget::timerEvent(event);
}

void SeaVipers2::mousePressEvent(QMouseEvent *event){
	if(img_area.contains(event->pos())){
		origin = event->pos();
		bb = QRect(origin, QSize());
		selecting = true;
	} else
		QWidget::mousePressEvent(event);
}

void SeaVipers2::mouseMoveEvent(QMouseEvent *event){
	if(selecting && img_area.contains(event->pos())){
		bb = QRect(origin, event->pos()).normalized();
		update(); // ready for qpaint event
	} else
		QWidget::mouseMoveEvent(event);
}

void SeaVipers2::mouseReleaseEvent(QMouseEvent *event){
	if(selecting)
		selecting = false;
	else
		QWidget::mouseReleaseEvent(event);
}
void SeaVipers2::handleLearningBoxChecked(void){
	if(ui.learningCheckBox->isChecked()){
		tracker.learningEnabled = true;
	} else 
		tracker.learningEnabled = false;
}
