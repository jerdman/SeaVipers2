#include "seavipers2.h"



SeaVipers2::SeaVipers2(QWidget *parent) : QMainWindow(parent){
	qDebug() << "Setting up main window";
	ui.setupUi(this);
	vidcap = cv::VideoCapture(2);
	video_timer = QBasicTimer();
	tracking = false;
	handleOpenCamera();
	frame = 0;

	outputFile.setFileName("c:\\Users\\tiger\\Desktop\\test\\log.csv");
	outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
	outputStream.setDevice(&outputFile);

	ranger = new Rangefinder(this);
	ranger->connectPort("COM7"); 
	connect(ranger, SIGNAL(distanceChanged()), ui.lcdNumber, SLOT(display()));

	ptu = new PanTilt(this);
	ptu->connectPort("COM7");

	//connections
	connect(ui.initializeButton, SIGNAL(clicked()), this, SLOT(handleStartTracker()));
	connect(ui.learningCheckBox, SIGNAL(clicked()), this, SLOT(handleLearningBoxChecked()));
	connect(ui.ptuResetButton, SIGNAL(clicked()), this, SLOT(handleResetButtonClicked()));
}

SeaVipers2::~SeaVipers2() {
	vidcap.release();
}

void SeaVipers2::handleResetButtonClicked(void){
	ptu->sendReset();
}

void SeaVipers2::handleOpenCamera(void){
	qDebug() << "Opening Camera";
	vidcap.open(-1);
	vidcap >> current_mat;
	vidcap >> current_mat;
	vidcap >> current_mat;
	vidcap >> current_mat;
	img_area = QRect(xOff, yOff, current_mat.cols, current_mat.rows);
	video_timer.start(1000.0/9.0, this); // 9 Hz, 11 fps
	imgCenter = QPoint(current_mat.cols / 2, current_mat.rows / 2);
	// 25deg * 19deg field of view for camera
	dxpp = 25.00 / current_mat.cols;
	dypp = 19.00 / current_mat.rows;
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
	if(!tracking)
		pnt.setPen(Qt::blue);
	else if(tracker.valid)
		if(tracker.currConf > 0.75)
			pnt.setPen(Qt::green);
		else
			pnt.setPen(Qt::yellow);
	else
		pnt.setPen(Qt::red);
	pnt.drawRect(bb);
}

void SeaVipers2::timerEvent(QTimerEvent *event){
	if(event->timerId() == video_timer.timerId()){
		// get next frame
		vidcap >> current_mat;
		frame++;
		if(tracking){
			tracker.processImage(current_mat);
			if(tracker.currBB){
				bb.setLeft(tracker.currBB->x + xOff);
				bb.setTop(tracker.currBB->y + yOff);
				bb.setWidth(tracker.currBB->width);
				bb.setHeight(tracker.currBB->height);
				int x, y;
				x = tracker.currBB->x + tracker.currBB->width / 2;
				y = tracker.currBB->y + tracker.currBB->height / 2;
				bbCenter = QPoint(x, y);
			}
			// ptu
			QLine l(imgCenter, bbCenter);
			if(l.dx() > 10 || l.dy() > 10) {
				ptu->panRelative(l.dx() * dxpp * 26133.00 / 220.00); // range of motion for pan, 220 deg
				ptu->tiltRelative(l.dy() * dypp * 28000.00 / 90.00); // range of motion for tilt, 90 deg
			} else {
				// on target; update range reading
				target_heading = ptu->getPan() / 26133.00 * 220.00;
				target_range = ranger->getDistance();
			}
		}
		cv::imwrite(QString("c:\\Users\\tiger\\Desktop\\test\\cap%1.jpg").arg(frame).toStdString().c_str(), current_mat);
		outputStream << frame << ',' << bb.x() << ',' << bb.y() << ',' << bb.width() << ',' << bb.height();
		if(tracking)
			outputStream << ",tracking,";
		else
			outputStream << ",not tracking,";
		outputStream << QString::number(tracker.currConf) << ',' << tracker.valid << ',';
		outputStream << QString::number(ranger->getDistance()) << ',';
		outputStream << QString::number(ptu->getPan()) << ',';
		outputStream << QString::number(ptu->getTilt()) << ',';
		outputStream << QString::number(target_heading) << ',' << QString::number(target_range);
		outputStream << "\n";
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
