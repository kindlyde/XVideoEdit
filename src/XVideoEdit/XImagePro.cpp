#include "XImagePro.h"

/*设置将要处理的图像帧*/
void XImagePro::set(cv::Mat mat1, cv::Mat mat2)
{
	this->src1 = mat1;
	this->src2 = mat2;
	mat1.copyTo(this->dst);
}

/*处理图像帧*/
void XImagePro::gain(double constast, double bright)
{
	src1.convertTo(dst, -1, constast, bright);
}

XImagePro::XImagePro()
{

}

XImagePro::~XImagePro()
{

}
