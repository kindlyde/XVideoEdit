#pragma once
#include <QThread>
#include <QMutex>
#include "opencv2/core.hpp"

/*����ģʽ��ֻ����һ������,����Ŀ��ֻ��һ��������Ƶ���߳�
*�������ģʽ����������һ��ȫ�ֱ���*/
class XVideoThread:public QThread
{
	Q_OBJECT

public:
	int fps = 0;
	bool isWrite = false;

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

	/*��ʼ����*/
	bool startExport(std::string  file, int width = 0, int height = 0);
	/*ֹͣ����*/
	void stopExport();

	virtual ~XVideoThread();

	/*�߳���ں���*/
	void run();

signals:
	void ViewImage1(cv::Mat mat);
	void ViewDes(cv::Mat mat);
	void SaveEnd();
protected:
	QMutex mutex;
	XVideoThread();
};

