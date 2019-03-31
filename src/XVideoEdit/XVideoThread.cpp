#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*1号视频源*/
static VideoCapture cap1;
bool isExit = false;

/*打开1号视频源*/
bool XVideoThread::open(const std::string file)
{
	cout << "open " << file << endl;
	mutex.lock();
	bool re = cap1.open(file);
	if (!re)
	{
		mutex.unlock();
		return re;
	}
	fps = cap1.get(CAP_PROP_FPS);

	mutex.unlock();
	cout << re << endl;
	return re;

}

/*获取视频播放进度*/
double XVideoThread::getPos()
{
	double pos = 0;

	mutex.lock();
	
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return pos;
	}
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	double cur = cap1.get(CAP_PROP_POS_FRAMES);
	if (count > 0.001)
		pos = cur / count;
	//cout << pos << endl;
	mutex.unlock();

	return pos;
}


void XVideoThread::seek(double pos)
{
	mutex.lock();

	if (!cap1.isOpened())
	{
		mutex.unlock();
		return ;
	}
	
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	int frame = (int)(count * pos);
	cap1.set(CAP_PROP_POS_FRAMES, frame);
	mutex.unlock();
}

void XVideoThread::run()
{
	Mat inImage;
	int s = 0;

	for (;;)
	{
		mutex.lock();

		if (isExit)
		{
			mutex.unlock();
			break;
		}

		if (!cap1.isOpened())
		{
			mutex.unlock();
			msleep(5);
			continue;
		}

		if ((!cap1.read(inImage)) || (inImage.empty()))
		{
			mutex.unlock();
			msleep(5);
			continue;
		}

		//显示图像,以信号槽的方式将图像地址传输出去
		ViewImage1(inImage);
		s = 1000 / fps;
		msleep(s);
		mutex.unlock();
	}
}

XVideoThread::XVideoThread()
{
	start();
}

XVideoThread::~XVideoThread()
{
	mutex.lock();
	isExit = true;
	mutex.unlock();
}
