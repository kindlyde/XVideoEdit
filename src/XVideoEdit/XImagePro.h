#pragma once
#include<opencv2/core.hpp>

class XImagePro
{
public:
	/*���ý�Ҫ�����ͼ��֡*/
	void set(cv::Mat mat1, cv::Mat mat2);

	/*��ȡ����õ�ͼ��֡*/
	cv::Mat get() { return dst; }

	/*����ͼ��֡*/
	void gain(double constast, double bright);

	XImagePro();
	~XImagePro();

private:
	/*����������*/
	cv::Mat src1, src2;
	cv::Mat dst;
};

