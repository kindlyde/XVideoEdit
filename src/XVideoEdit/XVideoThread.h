#pragma once
#include <QThread>
#include <QMutex>
#include "opencv2/core.hpp"

/*单例模式，只生成一个对象*/
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

	/*打开视频文件*/
	bool open(const std::string file);

	/*获取视频播放进度*/
	double getPos();

	/*滑动条控制播放进度*/
	void seek(double pos);

	virtual ~XVideoThread();

	/*线程入口函数*/
	void run();

signals:
	void ViewImage1(cv::Mat mat);

protected:
	QMutex mutex;
	XVideoThread();
};

