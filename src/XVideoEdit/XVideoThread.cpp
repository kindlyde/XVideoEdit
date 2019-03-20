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
	bool re = cap1.open(file);
	cout << re << endl;
	return re;

}

void XVideoThread::run()
{

}

XVideoThread::XVideoThread()
{
}


XVideoThread::~XVideoThread()
{
}
