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

	/*ȥ��������*/
	setWindowFlags(Qt::FramelessWindowHint);
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