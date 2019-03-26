#include "XVideoEidt.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <QPainter>

using namespace cv;

void XVideoEidt::setImage(cv::Mat mat)
{
	if (img.isNull())
	{
		uchar *buf = new uchar[width()*height() * 3];
		img = QImage(buf, width(), height(), QImage::Format_RGB888);
	}

	cv::Mat des;

	/*第一个Size为cv中大小函数，第二个为QImage成员函数*/
	cv::resize(mat, des, Size(img.size().width(), img.size().height()));

	cv::cvtColor(des,des,COLOR_BGR2RGB);

	memcpy(img.bits(), des.data, des.cols*des.rows*des.elemSize());

	update();
}

XVideoEidt::XVideoEidt(QWidget *p):QOpenGLWidget(p)
{
}

void XVideoEidt::paintEvent(QPaintEvent *e)
{
	QPainter p;
	p.begin(this);
	p.drawImage(QPoint(0, 0), img);
	p.end();
}

XVideoEidt::~XVideoEidt()
{

}
