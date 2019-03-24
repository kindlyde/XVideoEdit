#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*1号视频源*/
static VideoCapture cap1;

/*打开1号视频源*/
bool XVideoThread::open(const std::string file)
{
	cout << "open " << file << endl;
	mutex.lock();
	bool re = cap1.open(file);
	mutex.unlock();
	cout << re << endl;
	return re;

}

void XVideoThread::run()
{
	Mat inImage;

	for (;;)
	{
		mutex.lock();
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

		mutex.unlock();
	}
}

XVideoThread::XVideoThread()
{
}


XVideoThread::~XVideoThread()
{
}
