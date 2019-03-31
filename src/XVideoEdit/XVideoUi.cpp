#include "XVideoUi.h"
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include "XVideoThread.h"

using namespace std;

bool isPressed = FALSE;

XVideoUi::XVideoUi(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	/*去掉标题栏*/
	setWindowFlags(Qt::FramelessWindowHint);

	qRegisterMetaType<cv::Mat>("cv::Mat");

	/*建立信号槽函数*/
	QObject::connect(XVideoThread::get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.openGLWidget,
		SLOT(setImage(cv::Mat)));

	/*启动定时器*/
	startTimer(40);
}

void XVideoUi::open()
{
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("请选择视频文件"));
	if (name.isEmpty()) return;

	string file = name.toLocal8Bit().data();

	if (!(XVideoThread::get()->open(file)))
	{
		QMessageBox::information(this, "error", name+"open failed!");
	}

	/*类似的提示信息窗口，用于测试获取的文件路径*/
	//QMessageBox::information(this, "", name);

}

void XVideoUi::timerEvent(QTimerEvent *e)
{
	if (isPressed == TRUE) return;
	double pos = XVideoThread::get()->getPos();
	ui.palySlider->setValue(pos * 1000);
}

void XVideoUi::sliderMove()
{
	double pos = ui.palySlider->value();
	XVideoThread::get()->seek(pos/1000);
}

void XVideoUi::sliderPress()
{
	isPressed = TRUE;
}

void XVideoUi::sliderRelease()
{
	isPressed = FALSE;
}