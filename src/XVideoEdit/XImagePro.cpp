#include "XImagePro.h"

/*���ý�Ҫ�����ͼ��֡*/
void XImagePro::set(cv::Mat mat1, cv::Mat mat2)
{
	this->src1 = mat1;
	this->src2 = mat2;
	mat1.copyTo(this->dst);
}

/*����ͼ��֡*/
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
