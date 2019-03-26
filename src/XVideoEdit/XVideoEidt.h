#pragma once
#include <QOpenGLWidget>
#include <opencv2/core.hpp>

class XVideoEidt :public QOpenGLWidget
{
	Q_OBJECT

public:
	XVideoEidt(QWidget *p);
	void paintEvent(QPaintEvent *e);
	virtual ~XVideoEidt();

public slots:
	void setImage(cv::Mat mat);

protected:
	QImage img;
};

