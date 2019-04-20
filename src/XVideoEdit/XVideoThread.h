#pragma once
#include <QThread>
#include <QMutex>
#include "opencv2/core.hpp"

/*单例模式，只生成一个对象,本项目中只需一个处理视频的线程
*看申请的模式更像是申请一个全局变量*/
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

	/*打开视频文件*/
	bool open(const std::string file);

	/*获取视频播放进度*/
	double getPos();
	/*滑动条控制播放进度*/
	void seek(double pos);

	/*开始导出*/
	bool startExport(std::string  file, int width = 0, int height = 0);
	/*停止导出*/
	void stopExport();

	virtual ~XVideoThread();

	/*线程入口函数*/
	void run();

signals:
	void ViewImage1(cv::Mat mat);
	void ViewDes(cv::Mat mat);
	void SaveEnd();
protected:
	QMutex mutex;
	XVideoThread();
};

