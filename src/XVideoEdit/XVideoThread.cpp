#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*1����ƵԴ*/
static VideoCapture cap1;

/*��1����ƵԴ*/
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
