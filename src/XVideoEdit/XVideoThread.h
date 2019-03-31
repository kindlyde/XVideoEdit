#pragma once
#include <QThread>
#include <QMutex>
#include "opencv2/core.hpp"

/*����ģʽ��ֻ����һ������*/
class XVideoThread:public QThread
{
	Q_OBJECT

public:
	int fps = 0;

	static XVideoThread *get()
	{
		static XVideoThread vt;
		return &vt;
	}

	/*����Ƶ�ļ�*/
	bool open(const std::string file);

	/*��ȡ��Ƶ���Ž���*/
	double getPos();

	/*���������Ʋ��Ž���*/
	void seek(double pos);

	virtual ~XVideoThread();

	/*�߳���ں���*/
	void run();

signals:
	void ViewImage1(cv::Mat mat);

protected:
	QMutex mutex;
	XVideoThread();
};

