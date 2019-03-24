#pragma once
#include <QThread>
#include <QMutex>
#include "opencv2/core.hpp"

/*单例模式，只生成一个对象*/
class XVideoThread:public QThread
{
	Q_OBJECT

public:

	static XVideoThread *get()
	{
		static XVideoThread vt;
		return &vt;
	}

	/*打开视频文件*/
	bool open(const std::string file);

	virtual ~XVideoThread();

	/*线程入口函数*/
	void run();

signals:
	void ViewImage1(cv::Mat mat);

protected:
	QMutex mutex;
	XVideoThread();
};

