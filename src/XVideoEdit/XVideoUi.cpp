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

	/*ȥ��������*/
	setWindowFlags(Qt::FramelessWindowHint);

	qRegisterMetaType<cv::Mat>("cv::Mat");

	/*�����źŲۺ���*/
	QObject::connect(XVideoThread::get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.openGLWidget,
		SLOT(setImage(cv::Mat)));

	/*������ʱ��*/
	startTimer(40);
}

void XVideoUi::open()
{
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("��ѡ����Ƶ�ļ�"));
	if (name.isEmpty()) return;

	string file = name.toLocal8Bit().data();

	if (!(XVideoThread::get()->open(file)))
	{
		QMessageBox::information(this, "error", name+"open failed!");
	}

	/*���Ƶ���ʾ��Ϣ���ڣ����ڲ��Ի�ȡ���ļ�·��*/
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