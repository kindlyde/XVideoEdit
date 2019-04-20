#include "XVideoUi.h"
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include "XVideoThread.h"
#include "XVideoFilters.h"
#include "XVideoDebug.h"

using namespace std;

bool isPressed = false;
static bool isExport = false;

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

	/*UIģ�鸴��ͬһ������Թ���ͬһslot����
	*���������źŲ�*/
	QObject::connect(XVideoThread::get(),
		SIGNAL(ViewDes(cv::Mat)),
		ui.src2,
		SLOT(setImage(cv::Mat)));

	/*��Ƶ��������ź�*/
	QObject::connect(XVideoThread::get(),
		SIGNAL(SaveEnd()),
		this,
		SLOT(exportEnd()));

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

/*��Ƶ����*/
void XVideoUi::set()
{
	if (ui.bright->value() == 0
		&& ui.constast->value() == 1.0f)
	{
		return;
	}

	XTask task;
	task.type = XTASKTYPE_GAIN;
	task.para.push_back((double)ui.constast->value());
	task.para.push_back((double)ui.bright->value());

	/*���֮ǰ�����ڵ�Ԫ��*/
	XVideoFilters::get()->clear();

	/*����xvideoFilter����*/
	XVideoFilters::get()->add(task);
	MyDebug;
}

/*��Ƶ���������ֲ���ȡexport*/
void XVideoUi::exportVideo()
{
	QString name = QFileDialog::getSaveFileName(this, "save", "out1.avi");
	if (name.isEmpty()) return;

	/*�Ѿ���ʼ�����ˣ���Ŀǰ�ǹرյ�������*/
	if (isExport)
	{
		isExport = false;
		XVideoThread::get()->stopExport();
		ui.exportButton->setText("start export");
	}

	string file = name.toLocal8Bit().data();
	if (XVideoThread::get()->startExport(file, 0, 0))
	{
		/*���������ɹ�*/
		isExport = true;
		ui.exportButton->setText("stop export");
	}
	else
	{
		MyError;
	}
}

void XVideoUi::exportEnd()
{
	isExport = false;
	ui.exportButton->setText("start export");
}