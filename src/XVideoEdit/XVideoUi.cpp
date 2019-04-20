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

	/*去掉标题栏*/
	setWindowFlags(Qt::FramelessWindowHint);

	qRegisterMetaType<cv::Mat>("cv::Mat");

	/*建立信号槽函数*/
	QObject::connect(XVideoThread::get(),
		SIGNAL(ViewImage1(cv::Mat)),
		ui.openGLWidget,
		SLOT(setImage(cv::Mat)));

	/*UI模块复用同一个类可以共享同一slot函数
	*输出窗体的信号槽*/
	QObject::connect(XVideoThread::get(),
		SIGNAL(ViewDes(cv::Mat)),
		ui.src2,
		SLOT(setImage(cv::Mat)));

	/*视频导出完成信号*/
	QObject::connect(XVideoThread::get(),
		SIGNAL(SaveEnd()),
		this,
		SLOT(exportEnd()));

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

/*视频设置*/
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

	/*清空之前容器内的元素*/
	XVideoFilters::get()->clear();

	/*增加xvideoFilter任务*/
	XVideoFilters::get()->add(task);
	MyDebug;
}

/*视频导出，名字不可取export*/
void XVideoUi::exportVideo()
{
	QString name = QFileDialog::getSaveFileName(this, "save", "out1.avi");
	if (name.isEmpty()) return;

	/*已经开始导出了，则目前是关闭导出动作*/
	if (isExport)
	{
		isExport = false;
		XVideoThread::get()->stopExport();
		ui.exportButton->setText("start export");
	}

	string file = name.toLocal8Bit().data();
	if (XVideoThread::get()->startExport(file, 0, 0))
	{
		/*开启导出成功*/
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