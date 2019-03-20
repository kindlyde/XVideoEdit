#pragma once
#include <QThread>

/*����ģʽ��ֻ����һ������*/
class XVideoThread:public QThread
{
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

protected:
	XVideoThread();
};

