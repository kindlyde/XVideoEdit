#include "XVideoUi.h"
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include "XVideoThread.h"

using namespace std;

XVideoUi::XVideoUi(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	/*去掉标题栏*/
	setWindowFlags(Qt::FramelessWindowHint);
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