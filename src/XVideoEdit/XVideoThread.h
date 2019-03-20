#pragma once
#include <QThread>

/*单例模式，只生成一个对象*/
class XVideoThread:public QThread
{
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

protected:
	XVideoThread();
};

