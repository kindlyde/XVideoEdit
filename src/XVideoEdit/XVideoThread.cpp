#include "XVideoThread.h"
#include "XVideoFilters.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "XVideoDebug.h"

using namespace cv;
using namespace std;

/*1号视频源*/
static VideoCapture cap1;
static VideoWriter vw;

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

/*开始导出*/
bool XVideoThread::startExport(std::string  file, int width, int height)
{
	int widthExport = width, heightExport = height;
	
	seek(0);
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return false;
	}

	/*如果没有设置视频大小则保持原图大小*/
	if (width == 0 || height == 0)
	{
		widthExport  = cap1.get(cv::CAP_PROP_FRAME_WIDTH);
		heightExport = cap1.get(cv::CAP_PROP_FRAME_HEIGHT);
	}

	Size size(widthExport, heightExport);
	vw.open(file, CV_FOURCC('x', '2', '6', '4'), this->fps, size, true);

	if (!vw.isOpened())
	{
		mutex.unlock();
		return false;
	}

	isWrite = true;
	cout << "开始导出" << endl;
	mutex.unlock();
	return true;
}

/*停止导出*/
void XVideoThread::stopExport()
{
	mutex.lock();
	vw.release();
	isWrite = false;
	cout << "停止导出" << endl;
	mutex.unlock();
}

void XVideoThread::run()
{
	Mat inImage1,inImage2;
	Mat outImage;
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

		if ((!cap1.read(inImage1)) || (inImage1.empty()))
		{
			mutex.unlock();
			if (isWrite)
			{
				stopExport();
				SaveEnd();
			}
			msleep(5);
			continue;
		}

		outImage = XVideoFilters::get()->XPro(inImage1, inImage2);

		s = 1000 / fps;
		/*导出则暂停视频播放*/
		if (isWrite)
		{
			vw.write(outImage);
			s = 1;
		}
		else
		{
			//显示图像,以信号槽的方式将图像地址传输出去
			ViewImage1(inImage1);
			ViewDes(outImage);
		}

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
	wait();
}
