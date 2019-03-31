#pragma once
#include<opencv2/core.hpp>

class XImagePro
{
public:
	/*设置将要处理的图像帧*/
	void set(cv::Mat mat1, cv::Mat mat2);

	/*获取处理好的图像帧*/
	cv::Mat get() { return dst; }

	/*处理图像帧*/
	void gain(double constast, double bright);

	XImagePro();
	~XImagePro();

private:
	/*变量的申请*/
	cv::Mat src1, src2;
	cv::Mat dst;
};

