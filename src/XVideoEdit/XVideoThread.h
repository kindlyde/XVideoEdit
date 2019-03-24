#pragma once
#include <QThread>
#include <QMutex>
#include "opencv2/core.hpp"

/*����ģʽ��ֻ����һ������*/
class XVideoThread:public QThread
{
	Q_OBJECT

public:

	static XVideoThread *get()
	{
		static XVideoThread vt;
		return &vt;
	}

	/*����Ƶ�ļ�*/
	bool open(const std::string file);

	virtual ~XVideoThread();

	/*�߳���ں���*/
	void run();

signals:
	void ViewImage1(cv::Mat mat);

protected:
	QMutex mutex;
	XVideoThread();
};

